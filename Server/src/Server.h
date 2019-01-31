#ifndef _SERVER_
#define _SERVER_ 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

class Server
{
	private:
		int Socker_FD;
		int NewSocket;
		struct SocketAddr * Address;
		socklen_t OptLen;
		socklen_t AddrLen;
	public:
		Server(int Domain, int Type, int Protocol);
		~Server();
	
		int SetSocketOptions(int Level, int OptName, const void * OptVal) ;
		int Bind();
		int Listen(int Backlog);
		int Accept();
		int Connect();
}


#endif
