#include "ImageServer.h"

int main (void)
{
	char PortNumber[] = "1025";
        //char Filename [] = "hey.png";
        ImageServer Server(PortNumber);
	Server.Start();
        Server.ReceiveCycle();

}
