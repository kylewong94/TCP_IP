#include "ImageClient.h"

int main (int argc, char ** argv)
{
	char IPv4 [] = "71.92.199.189";
	char PortNumber [] = "25565";

	ImageClient LocalTest(IPv4, PortNumber);	
	LocalTest.Connect();

	LocalTest.SendConsoleMessages(argc, argv);
	//LocalTest.SendBytes(Msg2, Len2);
}
