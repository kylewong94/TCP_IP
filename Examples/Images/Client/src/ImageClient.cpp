
#include <poll.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <unistd.h>

#include "ImageClient.h"

using namespace std;

ImageClient::ImageClient(char * IPv4, char * PortNumber) : Client(IPv4, PortNumber)
{
}

ImageClient::~ImageClient()
{
}

int ImageClient::SendTwoBytes()
{
	int MsgLen = 6;
	char Msgs []= "Hello,World!";

	int NumMsgs = 2;
	
	struct pollfd pfds[1];
	pfds[0].fd = LocalSocket;
	pfds[0].events = POLLOUT;

	int num_events = 0;
	
	int i = 0;
	
	while(i < NumMsgs)
	{
		num_events = poll(pfds, 1, 2500);

		if(num_events == -1)
		{
			printf("poll\n");
			return -1;
		}
		else if (num_events == 0)
		{
			printf("Poll timed out! \n");
			return -1;
		}
		else
		{
			if(pfds[0].revents & POLLOUT)
			{
				int n = Send(&Msgs[MsgLen * i], MsgLen);
			}
		}
		i++;

	}
	
	return 0;
}

int ImageClient::SendConsoleMessages(int Num_Messages, char ** Messages)
{
	struct pollfd pfds[1];
	pfds[0].fd = LocalSocket;
	pfds[0].events = POLLOUT;

	int num_events = poll(pfds, 1, 2500);

	if(num_events == -1)
	{
		printf("poll\n");
		//return -1;
	}
	else if (num_events == 0)
	{
		printf("Poll timed out! \n");
		//return -1;
	}
	else
	{
		if(pfds[0].revents & POLLOUT)
		{
			int Data[] = {Num_Messages - 1};

			printf("Number of Message: %d\n", Data[0]);

			int Len = 4;
			int n = Send(Data, Len);
			
			SendMessages(Num_Messages, Messages);
		}
	}

	close(LocalSocket);
	
	return 0;

}

int ImageClient::SendMessages(int Num_Messages, char ** Messages)
{
	struct pollfd pfds[1];
	pfds[0].fd = LocalSocket;
	pfds[0].events = POLLOUT;

	int num_events = 0;
	
	string Msg;
	int i = 1;
	
	while(i < Num_Messages)
	{
		printf("Message %d: %s\n", i, Messages[i]);
		num_events = poll(pfds, 1, 2500);

		if(num_events == -1)
		{
			printf("poll\n");
			//return -1;
		}
		else if (num_events == 0)
		{
			printf("Poll timed out! \n");
			//return -1;
		}
		else
		{
			if(pfds[0].revents & POLLOUT)
			{
				Msg = Messages[i];
				int Len = Msg.length();	
				int n = Send(Messages[i], Len);
			}
		}
		i++;

	}
	
	return 0;
}
