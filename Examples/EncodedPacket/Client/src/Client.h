#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <signal.h>

///////////////////////////////////////////////////////////////////////
class Client
{
	protected:
		int    LocalSocket;
                int    Bytecount;
                int    SUCCESS_FLAG = true;

                unsigned char Buffer[10];

		struct addrinfo 	LocalAddr;
		struct addrinfo *	ServerInfo;
		struct addrinfo *	ptAddr;

	public:
		int ERR_FLAG;
		int RETURN_VAL;

		Client(char * INET4, char * PortNum);
		~Client();

		int Connect();
                int StartSend();
                int Receive();
		int SendInt(int * Data, int Len);
                int Send();
};
///////////////////////////////////////////////////////////////////////

