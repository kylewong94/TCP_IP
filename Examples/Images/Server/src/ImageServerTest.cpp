#include "ImageServer.h"

int main (void)
{
	char PortNumber[] = "1025";
	ImageServer Server(PortNumber);
	Server.Start();

	int n = Server.ReceiveMessages();
}
