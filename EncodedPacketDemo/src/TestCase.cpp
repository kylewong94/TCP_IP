
#include "DemoServer.h"

int main (void)
{
	char PortNumber[] = "1025";
	
	DemoServer ServerListenTest(PortNumber);
	ServerListenTest.ServerStart();
}
