#include "ImageClient.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
ImageClient::ImageClient(char * INET4, char * PortNum) : Client(INET4, PortNum)
{
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
ImageClient::~ImageClient()
{
        delete [] ImageBuffer;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void ImageClient::ReadImage(char * ImageName)
{
        FILE * ptImageFile = NULL; 
        if((ptImageFile = fopen(ImageName, "r")) == NULL)
        {
                printf("ImageClient::ReadImage() -  Failed to open file: %s\n",
                        ImageName);
                exit(-1);
        }
        else
        {
                printf("ImageClient::ReadImage() - File exists \n");
        }
        fseek(ptImageFile, 0, SEEK_END);
        ImageSize = ftell(ptImageFile);
        

        ImageBuffer = new unsigned char [ImageSize];

        rewind(ptImageFile);
        
        int Err;
        if((Err = fread(ImageBuffer, ImageSize, sizeof(char), ptImageFile)) < 1)
        {
                printf("ImageClient:: Failed to read image to buffer\n"); 
                exit(-1);
        }
        else
        {
                printf("ImageClient:: Read image to buffer: %i\n",
                        ImageSize); 
        } 
        fclose(ptImageFile);

}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
int ImageClient::SendImage()
{
        int Err;
        
        if((Err = send(LocalSocket, ImageBuffer, ImageSize, 0)) == -1)
        {
                printf("ImageClient:: cannot send image \n");
        }
        else
        {
                printf("ImageClient:: Successfully sent!\n");
        }
        close(LocalSocket);

        return Err;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void ImageClient::WriteImage()
{
        FILE * FileToWrite;

        if((FileToWrite = fopen("newImage_1.png", "w")) == NULL)
        {
                printf("Failed to write image - ImageClient::WriteImage()\n");
                exit(-1);
        }
        else
        {
                printf("ImageClient::WriteImage() - File created\n");
        }

        printf("Buffer size: %zu \n", sizeof(ImageBuffer));
        fwrite(ImageBuffer, 1, ImageSize, FileToWrite);
        fclose(FileToWrite);

        printf("ImageClient::WriteImage() - Image written\n");

}
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
int ImageClient::ReceiveImage()
{
        printf("Receiving Image . . .");
        int RetVal;
        int ImageSize = 2638; //Temporarily

        ImageBuffer = new unsigned char [ImageSize];
        
        if((RetVal = recv(LocalSocket, ImageBuffer, ImageSize, 0)) == -1)
        {
                printf("ImageClient::ReceiveImage() - Error could not"
                               " receive image\n");
                exit(-1);
        }
        else
        {
                printf("ImageClient::ReceiveImage() - Image in buffer! \n");
        }

        return RetVal;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
int ImageClient::SendPacketAmnt()
{
        int RetVal;
        if((RetVal = send(LocalSocket, &PacketsToSend, sizeof(PacketsToSend),
                                        0)) == -1)
        {
                printf("ImageClient::SendPacketAmnt() - Error could not send"
                                " Packet Amount \n");
                exit(-1);
        } 
        else
        {
                printf("ImageClient::SendPacketAmnt() - Send packet amount:"
                               " %i \n", PacketsToSend);
        }

        return RetVal;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void ImageClient::SendCycle()
{
        int Cycles     = 0;
        int ImageIndex = 0;
        int RetVal     = 0;
        PacketsToSend  = ImageSize/MaxSize;

        //First Send Packet Amount
        SendPacketAmnt();
        while(Cycles < PacketsToSend)
        {
                ImageIndex = MaxSize * Cycles;
                memset(&SendBuffer, 0,  MaxSize); 
                for(int IndexNo = 0; IndexNo < MaxSize; IndexNo++)
                {
                        SendBuffer[IndexNo] = ImageBuffer[ImageIndex];
                        ImageIndex++; 
                }
                printf("ImageClient::SendCycle() - Sending PacketNo: %i \n",
                                Cycles+1);

                while((RetVal = send(LocalSocket, &SendBuffer, MaxSize, 
                                                0)) < MaxSize)
                {
                        printf("ImageClient::SendCycle() - Failed to send "
                                        "PacketNo: %i \n", Cycles + 1);
                }
                #if 0
                if((RetVal = send(LocalSocket, &SendBuffer, MaxSize, 0)) == -1)
                {
                        printf("ImageClient::SendCycle() - Failed to send "
                                        "PacketNo: %i \n", Cycles + 1);
                        exit(-1);
                }
                else
                {
                        printf("ImageClient::SendCycle() -" 
                                      "  Sent PacketNo: %i \n", Cycles+1);
                        printf("ImageClient::SendCycle() - " 
                                        "Packets left: %i \n", 
                                        (PacketsToSend - (Cycles+1)));
                        Cycles++;
                }
                #endif
                        printf("ImageClient::SendCycle() -" 
                                      "  Sent PacketNo: %i \n", Cycles+1);
                        printf("Imageclient::SendCycle() -"
                                        " Sent: %i Bytes \n", RetVal);
                        printf("ImageClient::SendCycle() - " 
                                        "Packets left: %i \n", 
                                        (PacketsToSend - (Cycles+1)));
                        Cycles++;
        }
        
}
///////////////////////////////////////////////////////////////////////////////
