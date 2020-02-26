#ifndef _SERVER_
#define _SERVER_ 
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <signal.h>

#define MAX_CONNECTIONS 10

///////////////////////////////////////////////////////////////////////
class Server
{
	protected:
		int    HostSocket;
		int    AddressType; // 0 for IPv4 | 1 for IPv6 | 2 for unspecified

		struct addrinfo 	HostAddr;
		struct addrinfo *	ServInfo;
		struct addrinfo *	ptAddr;

	public:
		const static int   BUFFERSIZE = 64;
		char Buffer [BUFFERSIZE];

		int   ClientSocket;
		
		Server(char * PortNumber);
		~Server();
		int   ServerStart();
		int   Accept();
		int   Receive();
		int   Send();	
};
///////////////////////////////////////////////////////////////////////
#endif
