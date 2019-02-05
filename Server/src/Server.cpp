#include "Server.h"


Server::Server(int Domain, int Type, int Protocol, int PortID)
{	
	printf("Creating socket . . .");
	if((Socket_FD = socket(IPv4, TCP, 0)) == 0)
	{
		printf("Socket failed");
		exit(-1);
	}
	printf("Socket Created . . .");
}

Server::~Server()
{
	delete [] SocketAddr;
}

int SetSocketOptions(int Level, int OptName, const void * OptVal)
{
	if(setsockopt(Socket_FD, Level, 		
}
