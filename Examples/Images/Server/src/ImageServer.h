#pragma once
#include "Server.h"

///////////////////////////////////////////////////
class ImageServer : public Server
{
	private:
		const static int		BufferSize = 64;
		char			 		ImageBuffer[BufferSize];

	public:
		ImageServer(char * PortNum); 
		~ImageServer();		
		
		//int Accept();
		int ReceiveImage();

		int ReceiveInt(int * Data, int Len);

		int ReceiveMessages();
		int ReceiveNMessage(int n);

		int ReceiveAndWriteImageToFile(char * Filename);
		//int SendData();
};
///////////////////////////////////////////////////



