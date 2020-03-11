#include "Client.h"


int main (void)
{
<<<<<<< HEAD
	char IPv4 [] = "71.92.199.189";
	char PortNumber [] = "25565";
=======
	char IPv4 [] = "192.168.137.233";
	char PortNumber [] = "1025";
>>>>>>> 62a93572a906a19c5e13650f3a4d9bf91368da28

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
	LocalTest.SendInt();
//	LocalTest.SendInt(&GPSData.Lat, DataLen);
}
