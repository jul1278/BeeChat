// UDPServer.h
#ifndef _UDP_SERVER_H
#define _UDP_SERVER_H

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
#include "pthread.h"
#include "ClientMessage.h"

// UDPServer
class UDPServer
{
private:

	pthread_t listenerThread; 

	struct sockaddr_in serverAddress;

	bool stopListening; 

	socklen_t sockLen; 
	
	pthread_mutex_t messageQueueMutex; 
	pthread_mutex_t listenerMutex; 

	int serverSocket;

	std::queue<ClientMessage> clientMessageQueue; 

	void ListenForMessage( void* threadId );

public:

	UDPServer();
	~UDPServer(); 

	bool StartServer(); 
	void StopServer(); 

	void SendToClient( ClientMessage* clientMessage ); 

	bool IsUnreadMessages(); 
	void GetLatestMessage( ClientMessage* receivedClientMessage ); 
};

// _UDP_SERVER_H
#endif