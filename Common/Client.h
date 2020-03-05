#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <signal.h>

///////////////////////////////////////////////////////////////////////
class Client
{
	protected:
		int    			LocalSocket;
		
		struct addrinfo 	LocalAddr;
		struct addrinfo *	ptAddr;

	public:
		int ERR_FLAG;
		int RETURN_VAL;

		Client(char * INET4, char * PortNum);
		~Client();

		int Connect();
		int SendByte();
};
///////////////////////////////////////////////////////////////////////

