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
	int REUSEPORT = 1;

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
	delete [] ClientSockets;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////
int Server::ServerStart()
{
	int ConnectingFD;
	if (ptAddr == NULL)
	{
		fprintf(stderr, "Server: failed to bind \n");
		exit(1);
	}
	
	printf("Server: Listening \n"); 

	if(listen(HostSocket, BackLog) == -1) 
	{
		perror("listen");
		exit(1);
	}

	while(1)
	{
		ConnectingFD = accept(HostSocket, NULL, NULL);
		ClientSockets[ConnectedClients] = ConnectingFD;

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
			if (send(ClientSockets[ConnectedClients-1], "Hello World!", 13, 0) == -1)
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
