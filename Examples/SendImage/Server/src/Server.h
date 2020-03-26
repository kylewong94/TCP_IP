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
                int                     Bytecount; //Holder to count how many bytes were received from client 
                bool                     SUCCESS_FLAG = true; 
                //Buffer is to hold a max of 1024 bytes at a time
                unsigned char           Buffer[1024];
	
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
		int   Receive();
		int           Send(unsigned char * Buffer);
                int           Send_Flag();        
};
///////////////////////////////////////////////////////////////////////
