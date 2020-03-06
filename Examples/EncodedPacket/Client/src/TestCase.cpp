#include "Client.h"


int main (void)
{
	char IPv4 [] = "192.168.137.233";
	char PortNumber [] = "1025";

	Client LocalTest(IPv4, PortNumber);	
	LocalTest.Connect();

	struct GPS_Info
	{
		int Lat;
		int Long;
		int Deg;
	} GPSData;

	GPSData.Lat = 12;
	GPSData.Long = 100;
	GPSData.Deg = -45;
	
	int DataLen = 12;

	LocalTest.SendInt(&GPSData.Lat, DataLen);
}
