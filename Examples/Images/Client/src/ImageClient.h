#pragma once
#include "Client.h"

class ImageClient : public Client
{
	public:
		ImageClient(char * IPv4, char * PortNumber);
		~ImageClient();
		int SendTwoBytes();
	
		int SendConsoleMessages(int Num_Messages, char ** Messages);
		int SendMessages(int Num_Messages, char ** Messages);
};
