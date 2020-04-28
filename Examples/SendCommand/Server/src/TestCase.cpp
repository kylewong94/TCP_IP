#include "NetCommServer.h"

int main (void)
{
	char PortNumber[] = "1025";
        //char Filename [] = "hey.png";
        NetCommServer Server(PortNumber);
	Server.Start();
        Server.Cycle();

}
