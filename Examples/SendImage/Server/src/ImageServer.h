#pragma once
#include "Server.h"
#include <unistd.h>
///////////////////////////////////////////////////
class ImageServer : public Server
{
	private:
		unsigned char * ImageBuffer;
                uint32_t        ImageSize;
	public:
		ImageServer(char * PortNum);
		~ImageServer();		

                int  ReceiveImage();
                void  ReadImage(char * ImageName); 	
                int  SendImage();
                void WriteImage();
};
///////////////////////////////////////////////////



