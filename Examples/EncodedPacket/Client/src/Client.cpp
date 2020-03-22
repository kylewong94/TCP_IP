#include "Client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>


///////////////////////////////////////////////////////////////////////////////
Client::Client(char * IPv4, char * PortNum)
{
	int Err;
	// Clearing and setting values in LocalAddr
	memset(&LocalAddr, 0, sizeof LocalAddr);
	LocalAddr.ai_family   = AF_INET;
	LocalAddr.ai_socktype = SOCK_STREAM;

	//Setting Server info
	if((Err = getaddrinfo(IPv4, PortNum, &LocalAddr, &ServerInfo)) != 0)
	{
                printf("Client: Constructor - getaddrinfo failed\n");
	} 

}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
Client::~Client()
{
	freeaddrinfo(ptAddr);	
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
int Client::Connect()
{
	//Setting socket
	for(ptAddr = ServerInfo; ptAddr != NULL; ptAddr = ptAddr->ai_next)
	{
		if((LocalSocket = socket(ptAddr->ai_family, ptAddr->ai_socktype,
                                                    ptAddr->ai_protocol)) == -1)
		{
                        printf("Client: Could not set socket - Connect()\n");
			continue;
		}
		
		if((connect(LocalSocket, ptAddr->ai_addr, 
                                                     ptAddr->ai_addrlen)) == -1)
		{
                        printf("Client: Could not connect - Connect()\n");
			close(LocalSocket);
			continue;
		}
		
		break;
	}

	freeaddrinfo(ServerInfo);

	return 0;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
int Client::SendInt(int * Data, int Len)
{
	while(send(LocalSocket, Data, Len, 0) == -1);
	close(LocalSocket);

	return 0;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
int Client::Send()
{
	while(send(LocalSocket, Data, Len, 0) == -1);
	close(LocalSocket);

	return 0;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
int Client::Receive()
{
	while(send(LocalSocket, Data, Len, 0) == -1);
	close(LocalSocket);

	return 0;
}
///////////////////////////////////////////////////////////////////////////////
