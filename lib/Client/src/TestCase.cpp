#include "Client.h"


int main (void)
{
	char IPv4 [] = "192.168.137.233";
	char PortNumber [] = "1025";

	Client LocalTest(IPv4, PortNumber);	
	LocalTest.Connect();
	LocalTest.SendByte();
}
