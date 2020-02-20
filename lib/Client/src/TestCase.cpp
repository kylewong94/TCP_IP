#include "Client.h"


int main (void)
{
	char IPv4 [] = "127.0.0.1";
	char PortNumber [] = "1025";
	char HostName  [] = "blackpearl";

	Client LocalTest(IPv4, PortNumber, HostName);	
	LocalTest.Connect();
}
