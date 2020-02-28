#include "DemoServer.h"


int main (void)
{
	char PortNumber[] = "1025";
	char IPv4 []      = "192.168.1.1";	
	Server ServerListenTest(PortNumber);
	ServerListenTest.ServerStart();
}
