#include "Server.h"

int main (void)
{
	char PortNumber[] = "1025";
	Server ServerTest(PortNumber);
	ServerTest.Start();

	ServerTest.Receive();
}
