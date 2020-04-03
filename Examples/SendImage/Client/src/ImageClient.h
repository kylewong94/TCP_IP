#pragma once
#include "Client.h"
#include <stdint.h>
///////////////////////////////////////////////////////////////////////
class ImageClient : public Client
{
	private:
                const static int MaxSize = 512;
                int      PacketsToSend;

                unsigned char *  ImageBuffer;
                unsigned char    SendBuffer[MaxSize];
                uint32_t         ImageSize;
	public:
                ImageClient(char * INET4, char * PortNum);
                ~ImageClient();


                int  SendImage();
                int  ReceiveImage();
                int  SendPacketAmnt();
                void ReadImage(char * ptImage);
                void WriteImage();
                void SendCycle(); 
};
///////////////////////////////////////////////////////////////////////

