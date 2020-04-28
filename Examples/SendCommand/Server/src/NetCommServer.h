#pragma once
#include "Server.h"
#include <unistd.h>
///////////////////////////////////////////////////
class NetCommServer : public Server
{
	private:
               unsigned char RecvComm;
               unsigned char SendComm;

               unsigned char USERCOMM;
               unsigned char COMMS[5] = {0xF1, 0xF2, 0xF3};

	public:
		NetCommServer(char * PortNum);
		~NetCommServer();		

                void SendCommand();
                void Cycle();
};
///////////////////////////////////////////////////



