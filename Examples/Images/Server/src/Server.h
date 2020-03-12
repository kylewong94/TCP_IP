#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <signal.h>

///////////////////////////////////////////////////////////////////////
class Server
{
	protected:
		int    				HostSocket;
		int    				AddressType; // 0 for IPv4 | 1 for IPv6 | 2 for unspecified

		struct addrinfo 	HostAddr;
		struct addrinfo *	ServInfo;
		struct addrinfo *	ptAddr;

	public:
		int   				ClientSocket;
		
		Server(char * PortNumber);
		~Server();
		int   Start();
		int   Accept();
		int   Receive(void * Buffer, int BufferSize);
		int   Send();	
};
///////////////////////////////////////////////////////////////////////
