#pragma once
#include "Client.h"
#include <stdint.h>
#include <string>
///////////////////////////////////////////////////////////////////////
class NetComm : public Client
{
	private:
	        unsigned char RecvComm;
                unsigned char SendComm;
                //TAKEPIC, DELPIC, SHUTDOWN, SUCCESS, FAIL
                unsigned char COMMS[5] = {0xF1, 0xF2, 0xF3,0x0F, 0x01};

        public:
                NetComm(char * INET4, char * PortNum);
                ~NetComm();


               void ReceiveCommand();
               void ProcessCommand();
               void SendSuccess();
               void RunCycle();
               void TakePic();
               void DelPic();
               void ShutDown();
};
///////////////////////////////////////////////////////////////////////

