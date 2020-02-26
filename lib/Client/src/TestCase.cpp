#include "Client.h"


int main (void)
{
	char IPv4 [] = "172.20.10.10";
	char PortNumber [] = "1025";
	char HostName  [] = "blackpearl";

	Client LocalTest(IPv4, PortNumber, HostName);	
	LocalTest.Connect();
}
