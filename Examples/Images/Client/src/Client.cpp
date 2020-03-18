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


/////////////////////////////////////////////////////////////////////////
Client::Client(char * IPv4, char * PortNum)
{
	int Err;
	// Clearing and setting values in LocalAddr
	memset(&LocalAddr, 0, sizeof LocalAddr);
	LocalAddr.ai_family   = AF_INET;
	LocalAddr.ai_socktype = SOCK_STREAM;

	//Setting Server info
	if((RETURN_VAL = getaddrinfo(IPv4, PortNum, &LocalAddr, &ServerInfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s \n", gai_strerror(RETURN_VAL));
	} 

}
/////////////////////////////////////////////////////////////////////////
Client::~Client()
{
	freeaddrinfo(ptAddr);	
}
/////////////////////////////////////////////////////////////////////////
int Client::Connect()
{
	//Setting socket
	for(ptAddr = ServerInfo; ptAddr != NULL; ptAddr = ptAddr->ai_next)
	{
		if((LocalSocket = socket(ptAddr->ai_family, ptAddr->ai_socktype, ptAddr->ai_protocol)) == -1)
		{
			perror("client: socket");
			continue;
		}
		
		if((connect(LocalSocket, ptAddr->ai_addr, ptAddr->ai_addrlen)) == -1)
		{
			close(LocalSocket);
			perror("client: connect");
			continue;
		}
		
		break;
	}

	if(ptAddr == NULL)
	{
		fprintf(stderr, "client failed to connected \n");
		return -1;
	}

	freeaddrinfo(ServerInfo);

	return 0;
}

/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
int Client::Send(void * Data, int Len)
{
	send(LocalSocket, Data, Len, 0);
	//close(LocalSocket);

	return 0;
}
/////////////////////////////////////////////////////////////////////////
