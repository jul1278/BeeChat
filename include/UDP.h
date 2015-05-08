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

struct ThreadInfo
{

	unsigned int threadId; 
	char* messageBuffer; 



};

// UDPConnection class
class UDPConnection
{
private:

	int port; 
	int bufferSize; 
	char* buffer; 

	// shared mutex this
	bool stopListening = false; 

	pthread_mutex_t messageQueueMutex; 
	pthread_mutex_t listenerMutex; 

	std::queue<char* message> messageQueue; 

	//---------------------------------------------------------------------------
	// Name: ListenForMessage
	// Desc:
	//---------------------------------------------------------------------------
	void* ListenForMessage( void* threadInfo)
	{

		char* messageBuffer = new char[MESSAGE_LENGTH]; 

		while ( 1 ) {
			// Check if we've been asked to quit
			pthread_mutex_lock( &listenerMutex ); 

				if ( stopListening ) {
					break;  
				}

			pthread_mutex_unlock( &listenerMutex );


			pthread_mutex_lock( )

			int receivedBytes = recvfrom( serverSocket, messageBuffer, MESSAGE_LENGTH, 0, (struct sockaddr*)&clientAddress, &sockLen ); 

			if ( receivedBytes == -1 ) {
				// error
				// what do we do here



			} else {

				pthread_mutex_lock( &messageQueueMutex ); 

				char* newMessageBuffer = new char[MESSAGE_LENGTH]; 

				messageQueue.push_back(newMessageBuffer); 

				pthread_mutex_unlock( &messageQueueMutext );

			}

		}

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
	// StartClient
	bool StartClient(std::string userMessage)
	{
		std::cout << "Starting client..." << std::endl; 

		int clientSocket; 
		struct sockaddr_in serverAddress;

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

	//StartServer
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
			std::cout << "socket() error" << std::endl; 
			return false; 
		}

		// only difference between client and server is that a server's socket is bound to a port
		if ( bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr) ) == -1) {
			std::cout << "bind() error" << std::endl; 
			return false; 
		}

		int recievedBytes; 

		// wait for a message
		for(int i = 0; i < 1000; i++ ) {

			std::cout << "Waiting for message..." << std::endl; 

			recievedBytes = recvfrom( serverSocket, buffer, bufferSize, 0, (struct sockaddr*)&clientAddress, &sockLen ); 
			
			// if we got anything
			if ( recievedBytes > 0 ) {

				// 
				std::cout << "Echo back to client." << std::endl;

				// echo back to the client
				if ( sendto( serverSocket, buffer, recievedBytes, 0, (struct sockaddr*)&clientAddress, sizeof(clientAddress) ) == -1 ) {
					std::cout << "Error echoing to client." << std::endl; 
				} 

				char* addressBytes = new char[sizeof(struct sockaddr_in)];

				memcpy( (void*)addressBytes, (void*)&clientAddress, sizeof(struct sockaddr_in) );    

				// print out the hex of the client address struct
				for ( int i = 0; i < sizeof(struct sockaddr_in); i++ ) {
					std::cout << std::hex << (int)addressBytes[i] << " ";  
				}

				std::cout << dec << std::endl << recievedBytes << std::endl; 

				// print the actual message we recieved
				buffer[recievedBytes] = 0; 
				std::cout << buffer << std::endl;

				delete[] addressBytes; 

			} else if ( recievedBytes < 0 ) {
				std::cout << "recvfrom() error" << std::endl;
				break; 
			}

			
		}

		std::cout << "Exiting" << std::endl; 

		close( serverSocket ); 

		return true; 
	}

};

// _UDP_CONNECTION
#endif 