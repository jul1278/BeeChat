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
const int MESSAGE_LENGTH = 512; 

// DTO for transferring messages and client info from the UDP layer to the chat connection

// Client/Message DTO 
// we don't have to delete memory this way
struct ClientMessage
{	
	ClientMessage() 
	{
		message = 0; 
	}
	// Constructor
	ClientMessage( const struct sockaddr_in clientSocketAddr, const char* messageData )
	{
		message = new char[MESSAGE_LENGTH]; 

		memcpy( (void*)this->message, (void*) messageData, MESSAGE_LENGTH  ); 
		this->address = clientSocketAddr; 
	}
	// Copy Constructor
	ClientMessage( const ClientMessage& clientMessage )
	{
		this->address = clientMessage.address; 
		this->message = new char[MESSAGE_LENGTH]; 
		memcpy( (void*)this->message, (void*) clientMessage.message, MESSAGE_LENGTH  );
	}

	// Destructor
	~ClientMessage() 
	{
		if ( message ) { 
			delete message; 
		}
	}

	struct sockaddr_in address; 
	char* message;
};

// _CLIENT_MESSAGE_H
#endif