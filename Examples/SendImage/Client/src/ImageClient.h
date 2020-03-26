#pragma once
#include "Client.h"
#include <stdint.h>
///////////////////////////////////////////////////////////////////////
class ImageClient : public Client
{
	private:
                unsigned char * ImageBuffer;
                uint32_t        ImageSize;
	public:
                ImageClient(char * INET4, char * PortNum);
                ~ImageClient();


                int  SendImage();
                void ReadImage(char * ptImage);
                void WriteImage();
                int  ReceiveImage(); 
};
///////////////////////////////////////////////////////////////////////

