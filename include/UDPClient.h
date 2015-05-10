// UDPClient.h
#ifndef _UDP_CLIENT_H
#define _UDP_CLIENT_H

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

// UDPClient
class UDPClient
{
private:

	pthread_t listenerThread; 

	int clientSocket; 

	struct sockaddr_in serverAddress;

	// shared mutex this
	bool stopListening; 

	pthread_mutex_t messageQueueMutex; 
	pthread_mutex_t listenerMutex; 

	std::queue<ClientMessage> clientMessageQueue; 

	void ListenForMessage( void* threadId ); 

	friend void* UDPClientListener( void* ); 

public:

	UDPClient();
	~UDPClient(); 

	void StartClient(); 
	void StopClient(); 

	void SendToServer( char* message ); 

	bool IsUnreadMessages(); 
	void GetLatestMessage( ClientMessage* message );
};

// _UDP_CLIENT_H
#endif