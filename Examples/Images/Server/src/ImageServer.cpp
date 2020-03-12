#include <fstream>
#include <poll.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "ImageServer.h"

using namespace std;

/////////////////////////////////////////////
ImageServer::ImageServer(char * PortNumber) : Server(PortNumber)
{
}
/////////////////////////////////////////////

/////////////////////////////////////////////
ImageServer::~ImageServer()
{
}
/////////////////////////////////////////////

int ImageServer::ReceiveInt(int * Data, int Len)
{
	return Receive(Data, Len);
}

/////////////////////////////////////////////
int ImageServer::ReceiveImage()
{
	memset(ImageBuffer, 0, sizeof ImageBuffer);

	int Len = Receive(ImageBuffer, BufferSize);
	if(Len == -1)
	{
		return -1;
	}
	
	// must divide by 4 since Len is originally in bytes
	Len = Len / 4;

	// print to console
	for(int i = 0; i < Len; i++)
	{
		printf("%d \t", ImageBuffer[i]);
	}
	
	return Len;
}
/////////////////////////////////////////////

/////////////////////////////////////////////
int ImageServer::ReceiveMessages()
{
	struct pollfd pfds[1];

	pfds[0].fd = ClientSocket;
	pfds[0].events = POLLIN;
	
	int num_events = poll(pfds, 1, 2500);
		
	if(num_events == -1)
	{
		printf("poll");
		return -1;
	}
	if(num_events == 0)
	{
		printf("Poll timed out!\n");
		return -1;
	}
	else
	{
		if(pfds[0].revents & POLLIN)
		{
			int Num_Msgs = 0;
			int NBytes = ReceiveInt(&Num_Msgs, 4);
			
			if(NBytes > 0)
			{
				printf("Number of Messages: %d\n", Num_Msgs);
				ReceiveNMessage(Num_Msgs);
			}
			else
			{
				if(NBytes == 0)
				{
					printf("pollserver: socket %d hung up\n", pfds[0].fd);
				}
				else
				{
					perror("recv");
				}
				close(pfds[0].fd);

			}
		}

	}

	return 0;
}

/////////////////////////////////////////////

/////////////////////////////////////////////
int ImageServer::ReceiveNMessage(int n)
{
	struct pollfd pfds[1];

	pfds[0].fd = ClientSocket;
	pfds[0].events = POLLIN;
	
	int num_events;

	int i = 0;

	while(i < n)
	{	
		memset(ImageBuffer, 0, sizeof ImageBuffer);
		num_events = poll(pfds, 1, 2500);
		
		if(num_events == -1)
		{
			printf("poll");
			return -1;
		}
		if(num_events == 0)
		{
			printf("Poll timed out!\n");
			return -1;
		}
		else
		{
			if(pfds[0].revents & POLLIN)
			{
				int NBytes = Receive(ImageBuffer, BufferSize);
				
				if(NBytes > 0)
				{
					printf("Message %d: %s\n", i, ImageBuffer);
				}
				else
				{
					if(NBytes == 0)
					{
						printf("pollserver: socket %d hung up\n", pfds[0].fd);
					}
					else
					{
						perror("recv");
					}
					close(pfds[0].fd);

				}

			}
		}

		i++;
	}

	return 0;
	
}	
/////////////////////////////////////////////

/////////////////////////////////////////////
int ImageServer::ReceiveAndWriteImageToFile(char * Filename)
{
	int Len = ReceiveImage();

	ofstream File;
	File.open(Filename);
	
	for(int i = 0; i < Len; i++)
	{
		File << ImageBuffer[i] << "\n";
	}

	File.close();

	return 0;
}
/////////////////////////////////////////////
