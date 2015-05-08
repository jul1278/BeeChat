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

#ifndef _UDP_CONNECTION_H
#define _UDP_CONNECTION_H

// message length is set to 512 bytes
#define MESSAGE_LENGTH 512

using namespace std; 

// Client/Message DTO 
// we don't have to delete memory this way
struct ClientMessage
{
	// Constructor
	ClientMessage( struct sockaddr_in clientSocketAddr, char* messageData )
	{
		message = new char[MESSAGE_LENGTH]; 

		memcpy( (void*)this->message, (void) messageData, MESSAGE_LENGTH  ); 
		this->address = clientSocketAddress; 
	}
	// Destructor
	~ClientMessage() 
	{
		if ( message ) { 
			delete message; 
		}

		if (  ) 
	}

	struct sockaddr_in address; 
	char* message
};

// UDPConnection class
class UDPConnection
{
private:

	int port; 
	int bufferSize; 
	char* buffer; 

	int clientSocket; 

	struct sockaddr_in serverAddress;

	// shared mutex this
	bool stopListening = false; 

	pthread_mutex_t messageQueueMutex; 
	pthread_mutex_t listenerMutex; 


	int serverSocket;

	int clientAddressLen; 

	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress; 
	socklen_t sockLen; 

	std::queue<ClientMessage> clientMessageQueue; 

	//---------------------------------------------------------------------------
	// Name: ListenForMessage
	// Desc:
	//---------------------------------------------------------------------------
	void* ListenForMessage( void* threadId )
	{
		struct sockaddr_in clientAddress; 
		char* messageBuffer = new char[MESSAGE_LENGTH]; 

		while ( 1 ) {

			// Check if we've been asked to quit
			pthread_mutex_lock( &listenerMutex ); 

			if ( stopListening ) {
				
				break;  
			}

			pthread_mutex_unlock( &listenerMutex );

			memset( (void*)messageBuffer, 0, MESSAGE_LENGTH ); 

			// don't lock until after we've received a message!
			// socket could be a different length when it comes back? 
			int receivedBytes = recvfrom( serverSocket, messageBuffer, MESSAGE_LENGTH, 0, (struct sockaddr*)&clientAddress, &sockLen ); 
			

			if ( receivedBytes == -1 ) {
				// error
				// help help help what do i do 

			} else {

				pthread_mutex_lock( &messageQueueMutex ); 

				// ClientMessage makes it's own copy of the messageBuffer
				messageQueue.push( ClientMessage(clientAddress, messageBuffer) ); 

				pthread_mutex_unlock( &messageQueueMutext );

			}
		}

		delete messageBuffer; 

		pthread_exit(0); 
	}

public:

	// UDPConnection
	UDPConnection()
	{
		port = 6969; 
		bufferSize = 2048; 
		buffer = new char[bufferSize]; 


		pthread_mutex_init( &messageQueueMutex, NULL ); 
		pthread_mutex_init( &listenerMutex, NULL ); 


	}
	~UDPConnection()
	{
		delete[] buffer; 
	}
	//-----------------------------------------------------------------------------
	// Name: LatestMessage
	// Desc:
	//-----------------------------------------------------------------------------
	void LatestMessage( struct ClientMessage* clientMessage )
	{
		// wait until the listener thread is done with the queue 
		pthread_mutex_lock( &messageQueueMutex ); 

		if ( !messageQueue.empty() ) {

			memcpy( (void*)messageQueue, (void*)messageQueue.front(), MESSAGE_LENGTH ); 
			messageQueue.pop(); 
		}

		pthread_mutex_unlock( &messageQueueMutex ); 
	}
	//-----------------------------------------------------------------------------
	// Name: SendToClient
	// Desc:
	//-----------------------------------------------------------------------------
	void SendToClient( struct ClientMessage* clientMessage )
	{

		// TODO: check if we're a legit server at the moment

		// TODO: should be "sizeof(struct sockaddr)" or "sizeof(clientAddress)" ???
		int res = sendto( serverSocket, clientMessage->message, MESSAGE_LENGTH, 0, (struct sockaddr*)clientMessage->address, sizeof(struct sockaddr) ); 

		if ( res  == -1 ) {
			// error what do  
		} 
	}
	//-----------------------------------------------------------------------------
	// Name: SendToServer
	// Desc:
	//-----------------------------------------------------------------------------
	void SendToServer( char* message )
	{
		//TODO: are we sure a server exists? 

		if ( sendto( clientSocket, message, MESSAGE_LENGTH, 0, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr) ) == -1 ) {
			std::cout << "sendto() error" << std::endl; 
		} 
	}
	//-----------------------------------------------------------------------------
	// Name: StartClient
	// Desc:
	//-----------------------------------------------------------------------------
	bool StartClient(std::string userMessage)
	{
		std::cout << "Starting client..." << std::endl; 

		hostent* pHost; 
		pHost = (hostent*) gethostbyname( (char*) "localhost" ); 

		// htonl and htons convert ints into 'network representations'
		serverAddress.sin_family = AF_INET; 
		serverAddress.sin_addr.s_addr = *((in_addr_t*)pHost->h_addr); 
		serverAddress.sin_port = htons(port); 

		int serverAddressLen = sizeof(serverAddress); 

		// get a socket
		clientSocket = socket( AF_INET, SOCK_DGRAM, 0 ); 

		if ( clientSocket == -1 ) {
			std::cout << "socket() error" << std::endl; 
			return false; 
		}

		std::string message; 

		message = userMessage; 

		if ( sendto( clientSocket, message.c_str(), message.length(), 0, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr) ) == -1 ) {
			std::cout << "sendto() error" << std::endl; 
		} 

		std::cout << "Sent message: " << message << std::endl; 

		// now wait and see if we get a message back
		for (int i = 0; i < 1000; i++) {
			
			int recievedBytes = recvfrom( clientSocket, buffer, bufferSize, 0, NULL, NULL ); 



			if ( recievedBytes > 0 ) {
				buffer[recievedBytes] = 0; 
				std::cout << serverAddress.sin_addr.s_addr << std::endl; 
				std::cout << "Recieved: " << buffer << std::endl; 	
				break; 
			}
		}

		close(clientSocket); 

		return true; 

	}
	//-----------------------------------------------------------------------------
	// Name: StartServer
	// Desc:
	//-----------------------------------------------------------------------------
	// TODO: 
	bool StartServer()
	{
		std::cout << "Starting server..." << std::endl; 

		int serverSocket = socket( AF_INET, SOCK_DGRAM, 0 ); 

		int clientAddressLen = 0; 

		struct sockaddr_in serverAddress;
		struct sockaddr_in clientAddress; 
		socklen_t sockLen; 

		serverAddress.sin_family = AF_INET; 
		
		serverAddress.sin_addr.s_addr = INADDR_ANY; 
		serverAddress.sin_port = htons(port); 

		if ( serverSocket == -1 ) {
			//std::cout << "socket() error" << std::endl; 
			// error throw exception
			return false; 
		}

		// only difference between client and server is that a server's socket is bound to a port
		// once this port has been bound to then you can't bind to it until it gets released
		if ( bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr) ) == -1 ) {
			// did we error because the port has already been bound or something else
			return false; 
		}

		return true;
	}

};

// _UDP_CONNECTION
#endif 