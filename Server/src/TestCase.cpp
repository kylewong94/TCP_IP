#include "Server.h"


int main (void)
{
	char * ipAdd = "123.456.78";
	Server ServerListenTest(ipAdd);
	ServerListenTest.ServerStart();
}
