#include "Server.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////
Server::Server(char * PortNumber)
{
	int Err = 0;
	int REUSEPORT = 1;

	memset(&HostAddr, 0, sizeof HostAddr);
	HostAddr.ai_family   = AF_INET;
	HostAddr.ai_socktype = SOCK_STREAM;
	HostAddr.ai_flags    = AI_PASSIVE;


	if ((Err = getaddrinfo(NULL, PortNumber, &HostAddr, &ServInfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo error: %s \n", gai_strerror(Err));
		exit(-1);
	}

	printf("\nSetting Host Addr Info . . .\n");
	for(ptAddr = ServInfo; ptAddr != NULL; ptAddr = ptAddr->ai_next)
	{

		printf("Setting Host Socket . . . \n");
		if(((HostSocket = socket(ptAddr->ai_family, ptAddr->ai_socktype, ptAddr->ai_protocol))) == -1)
		{
			perror("server: socket");
			continue;
		}
		
		printf("Setting Socket Options \n");
		if(setsockopt(HostSocket, SOL_SOCKET, SO_REUSEADDR, &REUSEPORT, sizeof(int)) == -1)
		{
			perror("setsockopt");
			exit(1);
		} 

		printf("Binding Host Socket to Port . . .\n");
		if(bind(HostSocket,ptAddr->ai_addr, ptAddr->ai_addrlen) == -1)
		{
			close(HostSocket);
			perror("server: bind");
			continue;
		}
		
		break;
	}

	freeaddrinfo(ServInfo);
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////
Server::~Server()
{
	freeaddrinfo(ptAddr);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////
int Server::ServerStart()
{
	if (ptAddr == NULL)
	{
		fprintf(stderr, "Server: failed to bind \n");
		return -1;
	}
	
	printf("Server: Listening \n"); 

	if(listen(HostSocket, 1) == -1) 
	{
		perror("listen");
		return -1;
	}

	Accept();
	Receive();	
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
int Server::Accept()
{
	
	if((ClientSocket = accept(HostSocket, NULL, NULL)) == -1)
	{
		printf("Client could not connect");
		return -1;
	}
	printf("Client is connected \n");
	
	return 0;
	
}
int Server::Receive()
{
	printf("Receiving State . . . \n");
	int DataLen; 	
	
	if((DataLen = recv(ClientSocket , Buffer, BUFFERSIZE-1, 0)) == -1)
	{
		perror("recv");
		return -1;
	}

	for(int i = 0; i < DataLen; i++)
	{
	}
 
	//printf("%s \n", Buffer);

	return 0;
}

int Server::Send()
{
	return 0;
}
