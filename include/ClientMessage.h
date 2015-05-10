// ClientMessage.h
#ifndef _CLIENT_MESSAGE_H
#define _CLIENT_MESSAGE_H


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <pthread.h>
#include <queue>
#include <cstring>


const int PORT = 6969;
const int MESSAGE_LENGTH = 256;

// DTO for transferring messages and client info from the UDP layer to the chat connection

// Client/Message DTO 
// we don't have to delete memory this way
struct ClientMessage
{
	struct sockaddr_in address; 
	char message[MESSAGE_LENGTH];
};

// _CLIENT_MESSAGE_H
#endif
