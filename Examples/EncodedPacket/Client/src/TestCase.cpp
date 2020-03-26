#include "Client.h"


int main (void)
{
//	char IPv4 [] = "71.92.199.189";
//	char PortNumber [] = "25565";

	char IPv4 [] = "127.0.0.1";
	char PortNumber [] = "1025";

        Client LocalTest(IPv4, PortNumber);	
	LocalTest.Connect();
#if 0
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
#endif

        //LocalTest.Receive();
}
