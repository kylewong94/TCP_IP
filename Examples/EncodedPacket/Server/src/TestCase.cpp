#include "GPSDataServer.h"

int main (void)
{
	char PortNumber[] = "1025";
	GPSDataServer Server(PortNumber);
	Server.Start();

}
