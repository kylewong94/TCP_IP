#include "GPSDataServer.h"

int main (void)
{
	char PortNumber[] = "1025";
	GPSDataServer Server(PortNumber);
	Server.Start();

	//Server.ReceiveGPSData();

	char Filename[] = "data.txt";
	Server.ReceiveAndWriteGPSDataToFile(Filename);
}
