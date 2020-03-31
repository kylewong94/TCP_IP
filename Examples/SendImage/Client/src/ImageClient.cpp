#include "ImageClient.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
        fwrite(ImageBuffer, 1, 2638, FileToWrite);
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
////////////////////////////////////////////////////////////////////////////////
