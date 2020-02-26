#include "Client.h"


int main (void)
{
<<<<<<< HEAD
	char IPv4 [] = "192.168.137.7";
	char PortNumber [] = "1025";
	char HostName  [] = "blackpearl";
=======
	char IPv4 [] = "71.92.199.189";
	char PortNumber [] = "25565";
>>>>>>> d7f1c9f251e681cbe7106f28feca7210c0edcfc1

	Client LocalTest(IPv4, PortNumber);	
	LocalTest.Connect();
	LocalTest.SendByte();
}
