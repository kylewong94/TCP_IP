#pragma once
#include "Server.h"

///////////////////////////////////////////////////
class ImageServer : public Server
{
	private:
		unsigned char * ImageBuffer;
	public:
		ImageServer(char * PortNum);
		~ImageServer();		

                int  ReceiveImage();
                void WriteImage();
                		
};
///////////////////////////////////////////////////



