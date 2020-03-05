#pragma once
#include "Server.h"

///////////////////////////////////////////////////
class GPSDataServer : public Server
{
	private:
		const static int		BufferSize = 64;
		int			 			GPSDataBuffer[BufferSize];

	public:
		GPSDataServer(char * PortNum); 
		~GPSDataServer();		
		
		//int Accept();
		int ReceiveGPSData();
		//int SendData();
		int ReceiveAndWriteGPSDataToFile(char * Filename);
};
///////////////////////////////////////////////////



