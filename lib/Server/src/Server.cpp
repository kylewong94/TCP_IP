#include "Server.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <stdlib.h>


Server::Server(int MaxClient)
{
	MaxClients = MaxClient
	ClientSockets = new int [MaxClient];
}
