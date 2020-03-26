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
	int RetVal = 0;
	int REUSEPORT = 1;

	memset(&HostAddr, 0, sizeof HostAddr);
	HostAddr.ai_family   = AF_INET;
	HostAddr.ai_socktype = SOCK_STREAM;
	HostAddr.ai_flags    = AI_PASSIVE;

        //Setting struct for host 
	if ((RetVal = getaddrinfo(NULL, PortNumber, &HostAddr, &ServInfo)) != 0)
	{
                printf("Server::Server cannot get addrinfo\n");
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
		        printf("Server::Server - Cannot set host socket()");
		}
                else
                {
                        printf("Server::Server - Host socket set\n");
                }       

		printf("Setting Socket Options \n");
		if(setsockopt(HostSocket, SOL_SOCKET, SO_REUSEADDR, &REUSEPORT,
                              sizeof(int)) == -1)
		{
		        printf("Server::Server - Cannot set socket options"
                                "setsockopt\n");
		} 
                else
                {
                        printf("Server::Server - Client set\n"); 
                }

		printf("Binding Host Socket to Port . . .\n");
		if((RetVal = bind(HostSocket,ptAddr->ai_addr, 
                                                ptAddr->ai_addrlen)) == -1)
		{
			close(HostSocket);
		        printf("Server::Server - Cannot bind socket bind()\n");	
		}
                else
                {
                        printf("Server::Server - Host socket binded bind()\n");
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
        int RetVal;
	
        printf("Server: Listening \n"); 
	if((RetVal =listen(HostSocket, 1)) == -1) 
	{
		printf("Server::Start() - Error listening\n");
	        RetVal = -1;	
	}
        else
        {
               RetVal = Accept();
        }
	return RetVal;
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
        }
       
	return Return_Val;
	
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
int Server::Send_Flag()
{
        printf("Sending received flag . . .\n");
        int Return_Val;
        if((Return_Val = send(ClientSocket, "SUCCESS", 7, 0)) == -1) 
        {
                Return_Val = -1;
                printf("Server: Failed to send through socket - Send_Flag()\n"); 
        }
        else
        {
                printf("Server: Send Sucess!\n"); 
        }

        return Return_Val;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
int Server::Send(unsigned char * Buffer)
{
        return 0;
}
////////////////////////////////////////////////////////////////////////////////
