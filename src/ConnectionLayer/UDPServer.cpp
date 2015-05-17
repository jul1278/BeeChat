// UDPServer.cpp
#include "ConnectionLayer/UDPServer.h"

//----------------------------------------------------------------------------------
// Name: UDPServer
// Desc:
//----------------------------------------------------------------------------------
UDPServer::UDPServer()
{
	serverAddress.sin_family = AF_INET; 	
	serverAddress.sin_addr.s_addr = INADDR_ANY; 
	serverAddress.sin_port = htons(PORT); 

	// get socket
	udpSocket = socket( AF_INET, SOCK_DGRAM, 0 ); 

	if ( udpSocket == -1 ) {
		// error throw exception
	}

	// difference between client and server is that a server's socket is bound to a port
	// once this port has been bound to then you can't bind to it until it gets released
	if ( bind( udpSocket, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr) ) == -1 ) {

		// did we error because the port has already been bound or something else
		std::cout << "bind() error" << std::endl; 
	}
}
//----------------------------------------------------------------------------------
// Name: ~UDPServer
// Desc:
//----------------------------------------------------------------------------------
UDPServer::~UDPServer()
{
	close( udpSocket ); 
}





