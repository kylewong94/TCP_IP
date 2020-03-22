#include "Server.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>

///////////////////////////////////////////////////////////////////////////////
Server::Server(char * PortNumber)
{
	int Err = 0;
	int REUSEPORT = 1;

	memset(&HostAddr, 0, sizeof HostAddr);
	HostAddr.ai_family   = AF_INET;
	HostAddr.ai_socktype = SOCK_STREAM;
	HostAddr.ai_flags    = AI_PASSIVE;

        //Setting struct for host 
	if ((Err = getaddrinfo(NULL, PortNumber, &HostAddr, &ServInfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo error: %s \n", gai_strerror(Err));
		exit(-1);
	}

        //Setting up Server to listen on socket
	printf("\nSetting Host Addr Info . . .\n");
	for(ServInfo = ServInfo; ServInfo != NULL; ServInfo = ServInfo->ai_next)
	{
		printf("Setting Host Socket . . . \n");
		if(((HostSocket = socket(ServInfo->ai_family, 
                     ServInfo->ai_socktype, ServInfo->ai_protocol))) == -1)
		{
		        printf("Server Error: Cannot set host socket - line 36");	
			continue;
		}
		
		printf("Setting Socket Options \n");
		if(setsockopt(HostSocket, SOL_SOCKET, SO_REUSEADDR, &REUSEPORT,
                              sizeof(int)) == -1)
		{
		        printf("Server Error: Setting Socket Options" 
                                "- line 44 \n");
			exit(1);
		} 

		printf("Binding Host Socket to Port . . .\n");
		if(bind(HostSocket,ServInfo->ai_addr, ServInfo->ai_addrlen) == -1)
		{
			close(HostSocket);
		        printf("Server Error: Cannot bind socket - line 53");	
			continue;
		}
	}
	
        freeaddrinfo(ServInfo);
	
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
Server::~Server()
{
	freeaddrinfo(ptAddr);
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
int Server::Start()
{
	if (ptAddr == NULL)
	{
		fprintf(stderr, "Server: failed to bind \n");
		return -1;
	}
        else
        {
                
        }        
	printf("Server: Listening \n"); 

	if(listen(HostSocket, 1) == -1) 
	{
		perror("listen");
		return -1;
	}

	Accept();
	//Receive();	
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
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
int Server::Receive(void * Buffer, int BufferSize)
{
	printf("Receiving State . . . \n");
	int DataLen; 	
	
	if((DataLen = recv(ClientSocket , Buffer, BufferSize, 0)) == -1)
	{
		perror("recv");
		return -1;
	}

	return DataLen;
}

int Server::Send()
{
	return 0;
}
