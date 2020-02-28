#include "Client.h"


int main (void)
{
<<<<<<< HEAD:legacy-files/testcases/TestCase.cpp
	char IPv4 [] = "71.92.199.189";
	char PortNumber [] = "25565";
=======
	char IPv4 [] = "192.168.137.233";
	char PortNumber [] = "1025";
>>>>>>> a0a76c83586704cf171153442aff1d0266aa8b29:lib/Client/src/TestCase.cpp

	Client LocalTest(IPv4, PortNumber);	
	LocalTest.Connect();
	LocalTest.SendByte();
}
