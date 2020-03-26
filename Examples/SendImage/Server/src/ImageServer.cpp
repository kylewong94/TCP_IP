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
