#ifndef _SERVER_
#define _SERVER_ 
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <signal.h>


///////////////////////////////////////////////////////////////////////
class Server
{
	private:
		int Socket;
		int NewSocket;
		//int PortID;
	
		char * ipAddress;
	
		struct addrinfo         SocketInfo;
		struct addrinfo *       ServerInfo;
		struct addrinfo *       BindHelper;
		struct sigaction        Cleaner;
		struct sockaddr_storage ClientInfo;

		socklen_t SocketInSize;
	public:
		Server(char * IP);
		//Server(int Port, unsigned char * IP);
		~Server();
	
		void *GetAddr(struct sockaddr * sa);	
		void ServerStart();
		int  SetSocketOptions();
		int  Bind();
		int Listen();
		int  Connect();
		//int  Clean();

		static void sigchld_handler(int s);
};
///////////////////////////////////////////////////////////////////////

#endif
