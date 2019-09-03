#include "Client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h> 
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT "780"



void * Client::GetAddr(struct sockaddr * sa)
	{
		if(sa->sa_family == AF_INET)
			{
				return &(((struct sockaddr_in*)sa)->sin_addr);
			}
				return &(((struct sockaddr_in6*)sa)->sin6_addr);
	}

Client::Client(char * IP, char * PID)
	{
		  int ErrorChecker;
			
		  if(IP != NULL)
			{
				ipAddress = new char [sizeof(IP)];
				ipAddress = IP;

				printf("\n Setting INET to %s", IP);
			}

		PortID = new char [sizeof(PID)];
		
		memset(&SocketInfo, 0, sizeof SocketInfo);
		
		SocketInfo.ai_family   = AF_UNSPEC;
		SocketInfo.ai_socktype = SOCK_STREAM;
		

		//Need to replace NULL (Find out what needs to be placed)
		if((ErrorChecker = getaddrinfo(NULL , PortID, &SocketInfo, &ServerInfo)) !=0)
		{
			fprintf(stderr, "\ngetaddrinfo: %s \n", gai_strerror(ErrorChecker));
			exit(-1);	
		}
		printf("\nClient Info \nClient IP: %s \nClient PortID: %s \n", ipAddress, PortID);
			
	}

Client::~Client()
	{
		delete [] ipAddress;
		delete [] PortID;
		delete [] ServerInfo;
		delete [] BindHelper;
	}

int Client::Bind()
{
	int BuffSize;
	int yes = 1;
	printf("Starting Binding Process . . .\n");
	printf("Looking for available addresses. . . \n");

	for(BindHelper = ServerInfo; BindHelper != NULL; BindHelper = BindHelper->ai_next)
	{
		if ((Socket = socket(BindHelper->ai_family, BindHelper->ai_socktype, BindHelper->ai_protocol))
			== -1)
		{
			perror("Client: Socket");
			continue;
		}
	
		if(connect(Socket, BindHelper->ai_addr, BindHelper->ai_addrlen) == -1 )
		{
			close(Socket);
			perror("client: connect");
			continue;
		}
		
		break;
	}
		

	if (BindHelper == NULL)
	{
		fprintf(stderr, "Client: Failed to connect\n");
		exit(-1);
	}
	

	inet_ntop(BindHelper->ai_family, GetAddr((struct sockaddr *)BindHelper -> ai_addr), ipAddress, sizeof ipAddress);
	
	printf("Client: connecting to %s \n", ipAddress);

	freeaddrinfo(ServerInfo);
	
	return 0;
}

int Client::Receive()
{
	char DataRecv[MAXDATASIZE];
	int BuffSize;
	if((BuffSize = recv(Socket, DataRecv, MAXDATASIZE - 1, 0)) == -1)
	{
		perror("recv");
		exit(-1);
	}
	
	DataRecv[BuffSize] = '\0';
	printf("\n Packet: %s \n", DataRecv);
	
	return 0;	
}

void Client::Close()
{
	close(Socket);
}
/*
int Client::Send(string Messsage)
{
	int BuffSize;
	
	if((BuffSize = sendto(SocketInfo
}
*/
