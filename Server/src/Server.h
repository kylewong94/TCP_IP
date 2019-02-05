#ifndef _SERVER_
#define _SERVER_ 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

#define TCP SOCK_STREAM
#define IPv4 AF_INET
#define IPv6 AF_INET6


#define LOCAL 0
#define REMOTE 1

class Server
{
	private:
		int Socket_FD;
		int NewSocket;
		struct SocketAddr * Address;
		socklen_t OptLen;
		socklen_t AddrLen;
		int PortID;
		int NetworkConnectionType;
	public:
		Server(int Domain, int Type, int Protocol, int PortID, int NetworkConnectionType);
		~Server();
		int SetSocketOptions(int Level, int OptName, const void * OptVal);

		int Bind_Local();
		int Listen_Local();
		int Accept_Local();
		int Connect_Local();
	
		int Bind();
		int Listen(int Backlog);
		int Accept();
		int Connect();
}


#endif
