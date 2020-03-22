#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GPSDataServer.h"

using namespace std;

/////////////////////////////////////////////
GPSDataServer::GPSDataServer(char * PortNumber) : Server(PortNumber)
{
}
/////////////////////////////////////////////

/////////////////////////////////////////////
GPSDataServer::~GPSDataServer()
{
}
/////////////////////////////////////////////

/////////////////////////////////////////////
int GPSDataServer::ReceiveGPSData()
{
#if 0
        memset(GPSDataBuffer, 0, sizeof GPSDataBuffer);

	int Len = Receive(GPSDataBuffer, BufferSize);
	if(Len == -1)
	{
		return -1;
	}
	
	// must divide by 4 since Len is originally in bytes
	Len = Len / 4;

	// print to console
	for(int i = 0; i < Len; i++)
	{
		printf("%d \t", GPSDataBuffer[i]);
	}
	
	return Len;
#endif
        return 0;
}
/////////////////////////////////////////////

/////////////////////////////////////////////
int GPSDataServer::ReceiveAndWriteGPSDataToFile(char * Filename)
{
	int Len = ReceiveGPSData();

	ofstream File;
	File.open(Filename);
	
	for(int i = 0; i < Len; i++)
	{
		File << GPSDataBuffer[i] << "\n";
	}

	File.close();

	return 0;
}
/////////////////////////////////////////////
