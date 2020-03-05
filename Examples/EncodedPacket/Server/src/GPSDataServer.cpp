#include "GPSDataServer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
	memset(GPSDataBuffer, 0, sizeof GPSDataBuffer);

	int DataLen = Receive(GPSDataBuffer, BufferSize);
	if(DataLen == -1)
	{
		return -1;
	}
	
	DataLen = DataLen / 4;

	for(int i = 0; i < DataLen; i++)
	{
		printf("%d \t", GPSDataBuffer[i]);
	}
	
	return DataLen;
}
/////////////////////////////////////////////

/////////////////////////////////////////////
int GPSDataServer::WriteToFile()
{
	return 0;
}
/////////////////////////////////////////////
