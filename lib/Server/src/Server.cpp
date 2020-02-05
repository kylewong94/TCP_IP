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
Server::Server(int MaxClient, int BckLg, char * PortNumber)
{
	int Err = 0;

	BackLog = BckLg; 
	MaxClients = MaxClient;
	ClientSockets = new int [MaxClient];
	
	memset(&HostAddr, 0,sizeof HostAddr);
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
			fprintf(stderr, "Server: socket error: %s \n", gai_strerror(HostSocket));
			continue;
		}

		printf("Binding Host Socket to Port . . .\n");
		
		bind(HostSocket,ptAddr->ai_addr, ptAddr->ai_protocol);
		/*
		if((Err = bind(HostSocket,ptAddr->ai_addr, ptAddr->ai_protocol)) == -1)
		{
			close(HostSocket);
			fprintf(stderr, "Server: bind error: %s \n", gai_strerror(Err));
			continue;
		}
		*/
		break;
	}

	freeaddrinfo(ServInfo);
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////
Server::~Server()
{
	freeaddrinfo(ptAddr);
	delete [] ClientSockets;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////
int Server::ServerStart()
{
	if (ptAddr == NULL)
	{
		fprintf(stderr, "Server: failed to bind \n");
		exit(1);
	}
	
	printf("Server: Listening \n"); 

	while(listen(HostSocket, BackLog) != 0)
	{
		ClientSockets[ConnectedClients] = accept(ptAddr->ai_family, NULL, NULL);

		if(ClientSockets[ConnectedClients] == -1)
		{
			printf("Server: Could not connect client");
			continue;
		}
		else
		{
			ConnectedClients++;		
			printf("Server: Client Connected");
		}
		
		
		
		if (!fork())
		{
			close(HostSocket);
			if (send(ClientSockets[ConnectedClients], "Hello World!", 13, 0) == -1)
			{
				perror("Server: Send Error");
			}
			
			close(ClientSockets[ConnectedClients]);
			exit(0);
		}
		
		close(ClientSockets[ConnectedClients]);
		
	}
	
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
