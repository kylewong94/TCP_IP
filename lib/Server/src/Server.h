#ifndef _SERVER_
#define _SERVER_ 
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <signal.h>

#define MAX_CONNECTIONS 10

#define IPv4 0
#define IPv6 1
#define FREE 2
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
		int   BackLog;    //Max Queue
		int   MaxClients; //Maximum Clients allowed for this server
		int * ClientSockets; //Stores Socket for Clients
		int   ConnectedClients = 0;


		Server(int MaxClient, int BackLog, char * PortNumber);
		~Server();
		int   ServerStart();

};
///////////////////////////////////////////////////////////////////////

#endif
