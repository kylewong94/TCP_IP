#include "Server.h"


int main (void)
{
	char * ipAdd;
	
	ipAdd = new char [12];

	ipAdd = "10.110.112.0";
	Server ServerListenTest(ipAdd);
	ServerListenTest.ServerStart();
}
