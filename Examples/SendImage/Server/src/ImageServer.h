#pragma once
#include "Server.h"
#include <unistd.h>
///////////////////////////////////////////////////
class ImageServer : public Server
{
	private:
                const static uint16_t MaxSize = 4096; //Maximum size able to communicate through socket

                unsigned char * ImageBuffer;
                unsigned char   ReceiveBuffer[MaxSize];
                int             PacketsToSend; 
                uint32_t        ImageSize;
                
	public:
		ImageServer(char * PortNum);
		~ImageServer();		

                int   SendImage();
                int   ReceiveImage();
                void  Receive();   
                void  WriteImage();
                void  ReadImage(char * ImageName); 	
                void  ReceiveCycle();
};
///////////////////////////////////////////////////



