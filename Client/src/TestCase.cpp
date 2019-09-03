#include "Client.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>



int main()
{

	char IPAddress[20] = "10.110.112.0";
	char PortID[5] = "780";
	Client TestClient(IPAddress, PortID);
	
	TestClient.Bind();
	TestClient.Receive();
	TestClient.Close();

}
