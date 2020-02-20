#include "Server.h"


int main (void)
{
	char PortNumber[] = "1025";
	
	Server ServerListenTest(5, 10, PortNumber);
	ServerListenTest.ServerStart();
}
