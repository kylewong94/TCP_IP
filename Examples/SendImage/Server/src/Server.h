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
                struct addrinfo *       ptAddr;

	public:
		int   			ClientSocket;
		
		Server(char * PortNumber);
		~Server();
                int           Start();
                int           Begin();
		int           Accept();
                int           Send_Flag();        
};
///////////////////////////////////////////////////////////////////////
