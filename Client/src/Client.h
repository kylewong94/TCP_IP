#ifndef _CLIENT_
#define _CLIENT_

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <signal.h>


class Client
{
	private:
		int Socket;
		int NewSocket;
		int MAXDATASIZE = 100;
		
		char * PortID;
		char * ipAddress;
		struct addrinfo		SocketInfo;
		struct addrinfo *	ServerInfo;
		struct addrinfo *	BindHelper;
		struct sigaction	Cleaner;
		struct sockaddr_storage ClientInfo;

		socklen_t	SocketInSize;

	public:
		Client(char * IP, char * PID);
		~Client();

		void *GetAddr (struct sockaddr * sa);
		void Close();
		int Bind();
		int Listen();
		int Connect();
		int Receive();
		int Send(char DataSent[]);
		

		static void sigchld_handler(int s);	
};

#endif
