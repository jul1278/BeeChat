// UDPConnection.h
// threadsafe generic udp 
// Julian Pattie
#ifndef _UDP_CONNECTION_H
#define _UDP_CONNECTION_H

// TODO: are all of these really neccessary?
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
#include <pthread.h>



#include "ConnectionLayer/ClientMessage.h"

  
const int serverPort = 6969; 

// UDPConnection
class UDPConnection
{
	
// this is such a hack fix this 

public:

	std::queue<struct ClientMessage> messageQueue; 

	pthread_t listenerThread; 

	pthread_mutex_t messageQueueMutex; 
	pthread_mutex_t listenerThreadMutex; 

	bool stopListening;	//is this meant to be a function?

	void* ListenerThread( void* threadId ); 

	friend void* ServerListenerWrapper( void* threadId );
    friend void* ClientListenerWrapper( void* threadId );



	// server doesn't need to know it's own address
	struct sockaddr_in serverAddress;
	int udpSocket; 
	
	UDPConnection(); 
	~UDPConnection(); 

	// UDPServer will have to override this
	void Start(); 
	void Stop();

	bool IsUnreadMessages();

	void LatestMessage( struct ClientMessage* message ); 
	void SendMessage( struct ClientMessage* message ); 
};

#endif
