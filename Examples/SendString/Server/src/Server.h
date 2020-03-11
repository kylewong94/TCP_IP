#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <signal.h>

///////////////////////////////////////////////////////////////////////
class Server
{
	protected:
		static const int 	BufferSize = 64;
		char				Buffer[BufferSize];
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
		int   Receive();
		int   Send();	
};
///////////////////////////////////////////////////////////////////////
