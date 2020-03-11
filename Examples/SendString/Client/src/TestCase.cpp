//#include <fstream>
#include <string.h>
#include <stdio.h>

#include "Client.h"

int main (int argc, char ** argv)
{
	char IPv4 [] = "127.0.0.1";
	char PortNumber [] = "1025";

	Client LocalTest(IPv4, PortNumber);	
	LocalTest.Connect();
	
	LocalTest.SendHelloWorld();
	LocalTest.SendString();
}
