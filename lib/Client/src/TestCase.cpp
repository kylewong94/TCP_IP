#include "Client.h"


int main (void)
{
	char IPv4 [] = "71.92.199.189";
	char PortNumber [] = "25565";

	Client LocalTest(IPv4, PortNumber);	
	LocalTest.Connect();
}
