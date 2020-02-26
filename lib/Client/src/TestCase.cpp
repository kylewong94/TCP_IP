#include "Client.h"


int main (void)
{
	char IPv4 [] = "192.168.137.7";
	char PortNumber [] = "1025";
	char HostName  [] = "blackpearl";

	Client LocalTest(IPv4, PortNumber);	
	LocalTest.Connect();
	LocalTest.SendByte();
}
