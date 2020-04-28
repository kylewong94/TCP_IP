#include "NetComm.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
NetComm::NetComm(char * INET4, char * PortNum) : Client(INET4, PortNum)
{
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
NetComm::~NetComm()
{
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void NetComm::ReceiveCommand()
{
        int RetVal;
        unsigned short NetToUChar;
        if((RetVal = recv(LocalSocket, &NetToUChar, sizeof(short), 0)) == -1)
        {
                printf("NetComm::ReceiveCommand() - Could not receive command"
                               " \n");
                exit(-1);
        } 
        else
        {
                RecvComm = ntohs(NetToUChar);
                ProcessCommand();
        }
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void NetComm::ProcessCommand()
{
        if(RecvComm == COMMS[0])
        {
                TakePic();
                RecvComm = ' ';
        }
        else if(RecvComm == COMMS[1])
        {
                DelPic();
                RecvComm = ' ';
        }
        else if(RecvComm == COMMS[2])
        {
                ShutDown();
        }
        else
        {
                RecvComm = ' ';
        }
        /*
        else if(RecvComm == COMMS[3])
        {
                printf("SUCCESS! \n");
        } 
        else if(RecvComm == COMMS[4])
        {
                printf("FAIL! \n");
        }
        
        else
        {
                printf("ERROR \n");
        }
        */
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void NetComm::TakePic()
{
       printf("Take Pic Command receieved . . .\n");
       std::string Command = "python3 takepic.py";
       system(Command.c_str()); 
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void NetComm::DelPic()
{
      printf("Del Pic Command receieved . . .\n");
      std::string Command = "python3 delpic.py";
      system(Command.c_str());
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void NetComm::ShutDown()
{
        printf("SHUTDOWN SIG RECEIVED, SHUTTING DOWN . . . .\n");
        exit(-1);
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void NetComm::SendSuccess()
{
        int RetVal;
        if((RetVal = send(LocalSocket, &COMMS[5], sizeof(char), 0)) == -1)
        {
                printf("Send success failed \n");
        }
        else
        {
                printf("Send success true! \n");
        }
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void NetComm::RunCycle()
{
        while(RecvComm != COMMS[2])
        {
                ReceiveCommand();
        }
}
///////////////////////////////////////////////////////////////////////////////

