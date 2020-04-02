#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ImageServer.h"


////////////////////////////////////////////////////////////////////////////////
ImageServer::ImageServer(char * PortNumber) : Server(PortNumber)
{
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
ImageServer::~ImageServer()
{
        delete [] ImageBuffer;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
int ImageServer::ReceiveImage()
{
        printf("Receiving Image . . .");
        int RetVal;
        //int ImageSize = 160037;  
        
        if((RetVal = recv(ClientSocket, ReceiveBuffer, MaxSize, 0)) == -1)
        {
                printf("ImageServer::ReceiveImage() - Error could not"
                               " receive image\n");
                exit(-1);
        }
        else
        {
                printf("ImageServer::ReceiveImage() - "
                                "Bytes in buffer %i \n", RetVal);
        }
        
        return RetVal;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
int ImageServer::SendImage()
{
        //Under construction
        int Err;
        while((Err = send(ClientSocket, ImageBuffer, ImageSize, 0)) == -1);
        close(ClientSocket);

        return Err;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
void ImageServer::Receive()
{
        //We want to receive an integer that will tell us how many packets we
        //will need to stitch together an image
        //Will need to check if size received was 4 bytes (integer)
        uint8_t RetVal;
        if((RetVal = recv(ClientSocket, &PacketsToSend, sizeof(PacketsToSend),
                                        0)) == -1)
        {
                printf("ImageServer::Receive() - Error could not" 
                                "receive bytes \n");
                exit(-1);
        }     
        else
        {
                printf("ImageServer::Receive() - " 
                                "Amount of cycles needed %i \n", PacketsToSend);
        }

        ImageSize = MaxSize * PacketsToSend;
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
void ImageServer::WriteImage()
{
        FILE * FileToWrite;

        if((FileToWrite = fopen("SentImage_1.jpeg", "w")) == NULL)
        {
                printf("ImageServer::WriteImage() - Failed to create file\n");
                exit(-1);
        }
        else
        {
                printf("ImageServer::WriteImage() - File created\n");
        }

        fwrite(ImageBuffer, 1, ImageSize, FileToWrite);
        fclose(FileToWrite);

        printf("ImageClient::WriteImage() - Image written\n");
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
void ImageServer::ReadImage(char * ImageName)
{
        FILE * ptImageFile = NULL; 
        if((ptImageFile = fopen(ImageName, "r")) == NULL)
        {
                printf("ImageServer::ReadImage() -  Failed to open file: %s\n",
                        ImageName);
                exit(-1);
        }
        else
        {
                printf("ImageServer::ReadImage() - File exists \n");
        }
        fseek(ptImageFile, 0, SEEK_END);
        ImageSize = ftell(ptImageFile);
        
        ImageBuffer = new unsigned char [ImageSize];

        rewind(ptImageFile);
        
        int Err;
        if((Err = fread(ImageBuffer, ImageSize, sizeof(char), ptImageFile)) < 1)
        {
                printf("ImageServer::ReadImage() - Failed to "
                                "read image to buffer\n"); 
                exit(-1);
        }
        else
        {
                printf("ImageServer::ReadImage() - Read image to buffer: %i\n",
                        ImageSize); 
        } 
        fclose(ptImageFile);


}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
void ImageServer::ReceiveCycle()
{
        //Under construction
        //We receive the total amount of packets that will be sent through the
        //socket
        // Fills PacketsToSend
        Receive();
        
        int Cycles     = 0;
        int ImageIndex = 0;
        int RetVal     = 0;

        ImageBuffer = new unsigned char [ImageSize];

        printf("ImageServer::ReceiveCycle() - Total Packets needed to "
                        "process: %i \n", PacketsToSend);
        while(Cycles < PacketsToSend)
        {
               ImageIndex = MaxSize*Cycles;
               //Grab 4096 bytes from socket
               while((RetVal = ReceiveImage()) < 4000)
               {
                        printf("ImageServer::ReceiveCycle() - Error could not"
                                        " receive PacketNo: %i \n", (Cycles+1));
                        printf("ImageServer::ReceiveCycle() - Total bytes "
                                        "received: %i \n", RetVal);
               }
               #if 0
               if((RetVal = ReceiveImage() ) < 4000)
               {
                        printf("ImageServer::ReceiveCycle() - Error could not"
                                        " receive PacketNo: %i \n", (Cycles+1));
                        printf("ImageServer::ReceiveCycle() - Total bytes "
                                        "received: %i \n", RetVal);
                        exit(-1);
               }
               else
               {
                        printf("ImageServer::ReceiveCycle() - Processing "
                                        "PacketNo: %i \n", (Cycles+1));
               }
               #endif
               //Writing Buffer to ImageBuffer
               for(int IndexNo = 0; IndexNo < MaxSize; IndexNo++)
               {
                       ImageBuffer[ImageIndex] = ReceiveBuffer[IndexNo];
                       ImageIndex++;
               } 
               //Increase cycle
               Cycles++;

        }

        WriteImage();
}
////////////////////////////////////////////////////////////////////////////////

