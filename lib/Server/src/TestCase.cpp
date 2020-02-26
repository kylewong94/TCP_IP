#include "Server.h"


int main (void)
{
	char PortNumber[] = "1025";
	
	Server ServerListenTest(PortNumber);
	ServerListenTest.ServerStart();
}
