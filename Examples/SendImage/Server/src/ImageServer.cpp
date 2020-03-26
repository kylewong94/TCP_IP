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
        int ImageSize = 160037; //Temporarily
        ImageBuffer = new unsigned char [ImageSize];
        
        if((RetVal = recv(ClientSocket, ImageBuffer, ImageSize, 0)) == -1)
        {
                printf("ImageServer::ReceiveImage() - Error could not"
                               " receive image\n");
                exit(-1);
        }
        else
        {
                printf("ImageServer::ReceiveImage() - Image in buffer! \n");
        }

        return RetVal;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
void ImageServer::WriteImage()
{
        FILE * FileToWrite;

        if((FileToWrite = fopen("SentImage_1.jpeg", "w")) == NULL)
        {
                printf("ImageClient::WriteImage() - Failed to create file\n");
                exit(-1);
        }
        else
        {
                printf("ImageClient::WriteImage() - File created\n");
        }

        fwrite(ImageBuffer, 1, 160037, FileToWrite);
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
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
int ImageServer::SendImage()
{
        int Err;
        while((Err = send(ClientSocket, ImageBuffer, ImageSize, 0)) == -1);
        close(ClientSocket);

        return Err;
}
////////////////////////////////////////////////////////////////////////////////
