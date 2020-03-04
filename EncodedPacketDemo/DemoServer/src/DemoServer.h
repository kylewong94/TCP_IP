#pragma once
#include "Server.h"

///////////////////////////////////////////////////
class DemoServer : public Server
{
	public:
		DemoServer(char * PortNum); 
		~DemoServer();		
		
		int Accept();
		int Receive();
		int Send();
		int WriteToFile();
		
};
///////////////////////////////////////////////////



