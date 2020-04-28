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
        else
        {
                printf("Successfully set address info\n");
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
        int RetVal = 0;
	//Setting socket
	for(ptAddr = ServerInfo; ptAddr != NULL; ptAddr = ptAddr->ai_next)
	{
                printf("Setting socket information \n");
		if((LocalSocket = socket(ptAddr->ai_family, ptAddr->ai_socktype,
                                                    ptAddr->ai_protocol)) == -1)
		{
                        printf("Client: Could not set socket - Connect()\n");
                        RetVal = -1;
			continue;
		}
                else
                {
                        printf("Successfully set socket information\n");
                }
		
                printf("Connecting to server \n");
		if((connect(LocalSocket, ptAddr->ai_addr, 
                                                     ptAddr->ai_addrlen)) == -1)
		{
                        printf("Client: Could not connect - Connect()\n");
			close(LocalSocket);
                        exit(-1);
		}
                else
                {
                        printf("Successfully connected to server\n");
                }
		
		break;
	}
        
	freeaddrinfo(ServerInfo);
#if 0 
        printf("Checking socket communication . . .\n");
        if((RetVal = Receive()) < 1)
        {
                printf("Socket communication error. . .\n");
        }
        else
        {
                printf("Socket communication success!\n");
        }
#endif	
        return RetVal;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/*
int Client::SendInt(int * Data, int Len)
{
	while(send(LocalSocket, Data, Len, 0) == -1);
	close(LocalSocket);

	return 0;
}
*/
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
int Client::Send()
{
        /*
	while(send(LocalSocket, Data, Len, 0) == -1);
//	close(LocalSocket);
*/
	return 0;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
int Client::Receive()
{
        printf("Receiving state . . .\n");
        int RecvData;
	if((RecvData = recv(LocalSocket, Buffer, sizeof(Buffer), 0)) == -1)
        {
                printf("Client - Error receive\n");        
        }
        else
        {
                printf("Bytes received: %i \n", RecvData);
        }

        for(int i = 0; i < 10; i++)
        {
                printf(" %c \n", Buffer[i]);
        }

	return RecvData;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
int StartSend(unsigned char * toSendBuffer)
{
        return 0;
}
///////////////////////////////////////////////////////////////////////////////
