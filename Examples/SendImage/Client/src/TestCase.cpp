#include "ImageClient.h"


int main (void)
{
//	char IPv4 [] = "71.92.194.204";
//	char PortNumber [] = "25565";

	char IPv4 [] = "127.0.0.1";
	char PortNumber [] = "1025";
//      char FileName [] = "picture.jpeg";

        ImageClient Tester(IPv4, PortNumber);
        Tester.Connect();
        Tester.ReceiveImage();
        Tester.WriteImage(); 
}
