#pragma once
#include "Server.h"

///////////////////////////////////////////////////
class GPSDataServer : public Server
{
	public:
		GPSDataServer(char * PortNum); 
		~GPSDataServer();		
		
		int Accept();
		int Receive();
		int Send();
		int WriteToFile();
		
};
///////////////////////////////////////////////////



