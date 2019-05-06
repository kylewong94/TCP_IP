#include "Server.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <stdlib.h>

#define BACKLOG 10
#define PortID  "780"

void Server::sigchld_handler(int s)
	{
		int saved_errno = errno;
		
		while(waitpid(-1, NULL, WNOHANG) > 0);

		errno = saved_errno;
	}

void *GetAddr(struct sockaddr *sa)
	{
		if(sa->sa_family == AF_INET)
		{
			return &(((struct sockaddr_in*)sa)->sin_addr);
		}
		
			return &(((struct sockaddr_in6*)sa)->sin6_addr);
	}

Server::Server(char * IP)
{	
	int ErrorChecker;
	printf("\nSetting INET to %s", IP);

	ipAddress = new char [sizeof(IP)];
	
	ipAddress = IP; 

	printf("\nCreating Socket . . . \n");
	memset(&SocketInfo, 0, sizeof SocketInfo);
	
	SocketInfo.ai_family   = AF_UNSPEC;
	SocketInfo.ai_socktype = SOCK_STREAM;
	SocketInfo.ai_flags    = AI_PASSIVE;

	if ((ErrorChecker = getaddrinfo(NULL, PortID, &SocketInfo, &ServerInfo)) != 0)
	{
		perror("Problem found in creation of socket, Program Exiting\n");
	} 
	printf("Socket creation successful . . .\n");
}

Server::~Server()
{
	delete [] ServerInfo;
	delete [] BindHelper;
}

void Server::ServerStart()
{
	Bind();
	Listen();
}

int Server::Bind()
{
	int yes = 1;
	printf("Starting Binding Process . . .\n");
	printf("Looking for available addresses. . . \n");

	for(BindHelper = ServerInfo; BindHelper != NULL; BindHelper = BindHelper->ai_next)
	{
		if ((Socket = socket(BindHelper->ai_family, BindHelper->ai_socktype, BindHelper->ai_protocol))
			== -1)
		{
			perror("Server: Socket");
			continue;
		}
	
		if(setsockopt(Socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		{
			perror("Server: Setting Socket Options");
			exit(1);
		}

		if(bind(Socket, BindHelper->ai_addr, BindHelper->ai_addrlen) == -1)
		{
			close(Socket);
			perror("Server: Binding");
			continue;
		}
	
		break;
	}
		
	freeaddrinfo(ServerInfo);

	if (BindHelper == NULL)
	{
		fprintf(stderr, "Server: Failed to Bind\n");
		exit(1);
	}

	printf("Bind successful . . .\n");
	
}

int Server::Listen()
	{
		if(listen(Socket, BACKLOG) == -1)
		{
			perror("listen");
			exit(1);
		}
		
		Cleaner.sa_handler = &sigchld_handler;
		sigemptyset(&Cleaner.sa_mask);
		Cleaner.sa_flags = SA_RESTART;

		if(sigaction(SIGCHLD, &Cleaner, NULL) == -1)
		{
			perror("Signal Action\n");
			exit(1);
		}

		printf("Server waiting for connections . . . \n");

		while(1)
		{
			SocketInSize = sizeof ClientInfo;
			NewSocket = accept(Socket, (struct sockaddr *)&ClientInfo, &SocketInSize);
			if(NewSocket == -1)
			{
				perror("Accepted Connection");
				continue;
			}
			else
			{
				perror("Problem with connection");
			}
		}
  

			inet_ntop(ClientInfo.ss_family, GetAddr((struct sockaddr *)&ClientInfo),
					ipAddress, sizeof ipAddress);

			printf("Server received connection from %s\n", ipAddress);

			if(!fork())
			{
				close(Socket);
				if(send(NewSocket, "Connection received from server", 13, 0) == -1)
				{
					perror("Could not transmit data . . . \n");
				}
				close(NewSocket);
				exit(0);
			}
			close(NewSocket);		
			return 0;
		}
	
/*
int Server::Clean()
	{
		int saved_errno = errno;

		while(waitpid(-1, NULL, WNOHANG) > 0);
	
		errno = saved_errno;
	}
*/

