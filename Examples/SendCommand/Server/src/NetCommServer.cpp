#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "NetCommServer.h"


////////////////////////////////////////////////////////////////////////////////
NetCommServer::NetCommServer(char * PortNumber) : Server(PortNumber)
{
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
NetCommServer::~NetCommServer()
{
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
void NetCommServer::SendCommand()
{
        int RetVal;
        unsigned short PreSend = htons(SendComm);
        if((RetVal = send(ClientSocket, &PreSend, sizeof(short), 0)) == -1)
        {
                printf("Could not send command \n");
        }
        else
        {
                printf("Presend: %u \n", PreSend);
                printf("SendComm: %x \n", SendComm);
                printf("Command sent \n");
        }
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
void NetCommServer::Cycle()
{
        char UserInput;
        printf("Enter a command: \n");
        printf("1 - Take Pic \n");
        printf("2 - Del Pic \n");
        printf("3 - ShutDown \n");

        scanf("%c", &UserInput);
        while(UserInput != '4')
        {
                switch(UserInput)
                {
                        case '1':
                                SendComm = COMMS[0];
                                SendCommand();
                                printf("Taking Picture. . .\n");
                                break;
                        case '2':
                                SendComm = COMMS[1];
                                SendCommand();
                                printf("Deleting Picture. . .\n");
                                break;
                        case '3':
                                SendComm = COMMS[2];
                                SendCommand();
                                printf("Shut down. . .\n");
                                break;
                       case '4':
                                printf("Closing Server . . .\n");
                }
                printf("Enter a command: \n");
                printf("1 - Take Pic \n");
                printf("2 - Del Pic \n");
                printf("3 - ShutDown \n");
                printf("4 - Close Server \n");
                scanf("%c", &UserInput);
        }
        
}

////////////////////////////////////////////////////////////////////////////////
