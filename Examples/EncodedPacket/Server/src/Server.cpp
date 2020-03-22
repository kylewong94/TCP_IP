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

////////////////////////////////////////////////////////////////////////////////
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

        // Setting up Server to listen on socket
        // Set socket->set socket options->bind socket to port
	printf("\nSetting Host Addr Info . . .\n");
	for(ptAddr = ServInfo; ptAddr != NULL; ptAddr = ptAddr->ai_next)
	{
		printf("Setting Host Socket . . . \n");
		if(((HostSocket = socket(ptAddr->ai_family, 
                     ptAddr->ai_socktype, ptAddr->ai_protocol))) == -1)
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
		if((Err = bind(HostSocket,ptAddr->ai_addr, ptAddr->ai_addrlen)) == -1)
		{
			close(HostSocket);
		        printf("Server Error: Cannot bind socket - line 53");	
			continue;
		}
	}
        freeaddrinfo(ServInfo);
	
}
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
Server::~Server()
{
	freeaddrinfo(ptAddr);
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
int Server::Start()
{
	if (ServInfo == NULL)
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
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
int Server::Accept()
{
        int Return_Val;	
	if((ClientSocket = accept(HostSocket, NULL, NULL)) == -1)
	{
		printf("Client could not connect\n");
		Return_Val = -1;
	}
        else
        {
                printf("Client successfully connected \n");
                Return_Val = Send_Flag();	
        }
        
	return Return_Val;
	
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
int Server::Receive()
{
        int Return_Val = 0;
	printf("Receiving State . . . \n");
        
        #if 0	
	if((DataLen = recv(ClientSocket , Buffer, BufferSize, 0)) == -1)
	{
                printf("Server: Receive Error - Line 116 \n");
	}
        #endif
	return Return_Val;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
int Server::Send_Flag()
{
        while(send(HostSocket, &SUCCESS_FLAG, sizeof(SUCCESS_FLAG), 0));
        /*
        int Return_Val = 0;
        if((Return_Val = send(HostSocket, &SUCCESS_FLAG, 
                                        sizeof(SUCCESS_FLAG), 0)) == -1)
        {
                Return_Val = -1;
                printf("Server: Failed to send through socket - Send_Flag()\n"); 
        }
        else
        {
                printf("Server: Send Sucess!\n"); 
        }
        */
        return 0;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
int Server::Send(unsigned char * Buffer)
{
        return 0;
}
////////////////////////////////////////////////////////////////////////////////
