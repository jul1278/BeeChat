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

using namespace std; 

// UDPConnection class
class UDPConnection
{
private:

	int port; 
	int bufferSize; 
	char* buffer; 

public:

	// UDPConnection
	UDPConnection()
	{
		port = 6969; 
		bufferSize = 2048; 
		buffer = new char[bufferSize]; 
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

		// now wait and see if we got a message back
		for (int i = 0; i < 100; i++) {
			
			int recievedBytes = recvfrom( clientSocket, buffer, bufferSize, 0, (struct sockaddr*) &serverAddress, (socklen_t*)&serverAddressLen ); 

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

		struct sockaddr_in serverAddress, clientAddress; 

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

			recievedBytes = recvfrom( serverSocket, buffer, bufferSize, 0, (struct sockaddr*)&clientAddress, (socklen_t*)&clientAddressLen ); 
			
			// if we got anything
			if ( recievedBytes > 0 ) {

				// echo back to the client
				sendto( serverSocket, buffer, bufferSize, 0, (struct sockaddr*)&clientAddress, sizeof(struct sockaddr) ); 

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