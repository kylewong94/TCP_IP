#pragma once
#include "Server.h"

///////////////////////////////////////////////////
class DemoServer : public Server
{
	public:
<<<<<<< HEAD:EncodedPacketDemo/DemoServer/src/DemoServer.h
		DemoServer(char * PortNumber);
		~DemoServer();		
=======
		DemoServer(char* PortNumber);
		~DemoServer();
		int Accept();
		int Receive();
		int Send();
>>>>>>> a0a76c83586704cf171153442aff1d0266aa8b29:EncodedPacketDemo/src/DemoServer.h
		int WriteToFile();
		
};
///////////////////////////////////////////////////



