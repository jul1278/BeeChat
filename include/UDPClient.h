// UDPClient.h
#define _UDP_CLIENT_H
#ifndef _UDP_CLIENT_H

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


const int PORT = 6969;
const int MESSAGE_LENGTH = 512; 

// UDPClient
class UDPClient
{
private:

	char* buffer; 

	int clientSocket; 

	struct sockaddr_in serverAddress;

	// shared mutex this
	bool stopListening = false; 

	pthread_mutex_t messageQueueMutex; 
	pthread_mutex_t listenerMutex; 

	std::queue<ClientMessage> clientMessageQueue; 

	void* ListenForMessage( void* threadId ); 

public:

	UDPClient();
	~UDPClient(); 

	void SendToServer( char* message ); 

	bool IsUnreadMessages(); 
	void GetLatestMessage( char* message ); 
};

// _UDP_CLIENT_H
#endif