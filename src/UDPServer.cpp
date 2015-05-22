// UDPServer.cpp
#include "UDPServer.h"

UDPConnection* serverlistener;

// wrapper function which is friends with UDPConnection
// we can't pass a pointer to a member function to a thread
void* ServerListenerWrapper(void* threadId)
{
    serverlistener->ListenerThread(threadId);
    return NULL;
}
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
        std::cout << "socket() error" << std::endl;
	}

	// difference between client and server is that a server's socket is bound to a port
	// once this port has been bound to then you can't bind to it until it gets released
	if ( bind( udpSocket, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr) ) == -1 ) {

		// did we error because the port has already been bound or something else
		std::cout << "bind() error" << std::endl; 
    } else {
        std::cout << "bind() successful" << std::endl; 
    }
    
    serverlistener = this;
    
}
//----------------------------------------------------------------------------------
// Name: ~UDPServer
// Desc:
//----------------------------------------------------------------------------------
UDPServer::~UDPServer()
{
	close( udpSocket ); 
}
//----------------------------------------------------------------------------------
// Name: Start
// Desc:
//----------------------------------------------------------------------------------
void UDPServer::Start()
{
    // check if a thread has already started

    int res = pthread_create( &listenerThread, NULL, ServerListenerWrapper, NULL );
    
    if ( res ) {
        // error
        std::cout << "pthread_error()" << std::endl;
    }
}





