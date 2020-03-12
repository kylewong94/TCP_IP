#include "ImageClient.h"

int main (int argc, char ** argv)
{
	char IPv4 [] = "127.0.0.1";
	char PortNumber [] = "1025";

	ImageClient LocalTest(IPv4, PortNumber);	
	LocalTest.Connect();

	LocalTest.SendConsoleMessages(argc, argv);
	//LocalTest.SendBytes(Msg2, Len2);
}
