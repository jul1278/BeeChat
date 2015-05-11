// UDPClient.h
#ifndef _UDP_CLIENT_H
#define _UDP_CLIENT_H

#include "UDPConnection.h"
#include "ClientMessage.h"

// UDPClient
class UDPClient : public UDPConnection
{
private:


public:

	UDPClient() 
	{	
		hostent* pHost; 
		pHost = (hostent*) gethostbyname( (char*) "localhost" ); 

		serverAddress.sin_addr.s_addr = *((in_addr_t*)pHost->h_addr); 
		serverAddress.sin_family = AF_INET; 	
		serverAddress.sin_port = htons(PORT);

		// we always need to get a socket
		//printf("Started client.\n");
		// get a socket
		udpSocket = socket( AF_INET, SOCK_DGRAM, 0 ); 

		if ( udpSocket == -1 ) {
			std::cout << "socket() error" << std::endl;  
		}


	}
	~UDPClient()
	{
		
	} 

	//
	void SendToServer( char* message )
	{
		ClientMessage clientMessage;

		memcpy( clientMessage.message, message, MESSAGE_LENGTH ); 

		clientMessage.address = serverAddress;  
		SendMessage( &clientMessage ); 
	}
};

// _UDP_CLIENT_H
#endif