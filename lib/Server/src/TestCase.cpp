#include "Server.h"


int main (void)
{
	char * PortNumber;
	
	PortNumber = new char [4];
	PortNumber = "1025";

	Server ServerListenTest(5, 10, PortNumber);
	ServerListenTest.ServerStart();
}
