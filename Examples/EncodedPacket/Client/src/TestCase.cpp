#include "Client.h"


int main (void)
{
	char IPv4 [] = "127.0.0.1";
	char PortNumber [] = "1025";

	Client LocalTest(IPv4, PortNumber);	
	LocalTest.Connect();

	struct GPS_Info
	{
		int Lat;
		int Long;
		int Deg;
	} GPSData;

	GPSData.Lat = -1;
	GPSData.Long = 420;
	GPSData.Deg = 69;
	
	int DataLen = 12;

	LocalTest.SendInt(&GPSData.Lat, DataLen);
}
