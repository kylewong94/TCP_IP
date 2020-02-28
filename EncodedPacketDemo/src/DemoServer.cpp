#include "DemoServer.h"
#include "Server.h"

#include "stdlib.h"
#include "stdio.h"

#include <iostream>

using namespace std;

/////////////////////////////////////////////
DemoServer::DemoServer(char* PortNumber) : Server(PortNumber)
{

}

DemoServer::~DemoServer()
{
	cout << "Deconstructor" << endl;
}

int DemoServer::WriteToFile()
{
	return 0;
}
