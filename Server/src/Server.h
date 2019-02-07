#ifndef _SERVER_
#define _SERVER_ 
#include <sys/socket.h>

class Server
{
	private:
		int Socket;
		int NewSocket;
		int PortID;
	
		char IP[INET6_ADDRSTRLEN];
	
		struct addrinfo         SocketInfo;
		struct addrinfo *       ServerInfo;
		struct addrinfo *       BindHelper;
		struct sigaction        Cleaner;
		struct sockaddr_storage ClientInfo;

		socklen_t SocketInSize;
	public:
		Server(int Port);
		~Server();
		
		void ServerStart();
		int SetSocketOptions();
		int Bind();
		int Listen();
		int Connect();
		int Clean();

		int * GetAddr(struct sockaddr * sa);
}


#endif
