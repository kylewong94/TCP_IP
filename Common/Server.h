#pragma once
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <signal.h>

///////////////////////////////////////////////////////////////////////
class Server
{
	protected:
		int                     HostSocket;

		struct addrinfo 	HostAddr;
		struct addrinfo *	ServInfo;
                
	public:
		int   			ClientSocket;
		
		Server(char * PortNumber);
		~Server();
                int   Start();
                int   Begin();
		int   Accept();
		int   Receive(void * Buffer, int BufferSize);
		int   Send();	
};
///////////////////////////////////////////////////////////////////////
