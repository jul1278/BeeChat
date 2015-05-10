// UDPServer.cpp
#include "UDPServer.h"

UDPServer* listenerServer; 

void* UDPServerListener(void* threadId)
{	
	listenerServer->ListenForMessage(threadId);
    return NULL;
}

//------------------------------------------------------------------
// Name: UDPServer
// Desc: 
//------------------------------------------------------------------
UDPServer::UDPServer()
{
	serverAddress.sin_family = AF_INET; 	
	serverAddress.sin_addr.s_addr = INADDR_ANY; 
	serverAddress.sin_port = htons(PORT); 

	pthread_mutex_init( &messageQueueMutex, NULL ); 
	pthread_mutex_init( &listenerMutex, NULL ); 

	listenerServer = this; 
}
//------------------------------------------------------------------
// Name: ~UDPServer
// Desc: 
//------------------------------------------------------------------
UDPServer::~UDPServer()
{
	pthread_mutex_destroy( &messageQueueMutex );
	pthread_mutex_destroy( &listenerMutex ); 
}
//------------------------------------------------------------------
// Name: StartServer
// Desc: 
//------------------------------------------------------------------
bool UDPServer::StartServer()
{
	// get socket
	serverSocket = socket( AF_INET, SOCK_DGRAM, 0 ); 

	if ( serverSocket == -1 ) {

		std::cout << "socket() error" << std::endl; 
		// error throw exception
		return false; 
	}

	// difference between client and server is that a server's socket is bound to a port
	// once this port has been bound to then you can't bind to it until it gets released
	if ( bind( serverSocket, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr) ) == -1 ) {

		// did we error because the port has already been bound or something else
		std::cout << "bind() error" << std::endl; 
		return false; 
	}

	// check if a thread has already started
	stopListening = false; 

	int threadId = 0; 

	int res = pthread_create( &listenerThread, NULL, UDPServerListener, NULL ); 

	if ( res ) {
		std::cout << "pthread_create() error." << std::endl; 
		return false; 
	}

	printf("Started server.\n"); 

	return true;
}
//------------------------------------------------------------------
// Name: StopServer
// Desc: 
//------------------------------------------------------------------
void UDPServer::StopServer()
{	
	pthread_mutex_lock( &listenerMutex ); 
	stopListening = true;
	pthread_mutex_unlock( &listenerMutex );
    
    close(serverSocket);
    
	pthread_exit(NULL);

	// what do
	
}
//------------------------------------------------------------------
// Name: SendToClient
// Desc: 
//------------------------------------------------------------------
void UDPServer::SendToClient( ClientMessage* clientMessage )
{
	// TODO: check if we're a legit server at the moment

	// TODO: should be "sizeof(struct sockaddr)" or "sizeof(clientAddress)" ???
	int res = sendto( serverSocket, clientMessage->message, MESSAGE_LENGTH, 0, (struct sockaddr*)&clientMessage->address, sizeof(struct sockaddr) );

	if ( res  == -1 ) {
		std::cout << "UDPServer::SendToClient() sendto() error." << std::endl; 
	}
}
//------------------------------------------------------------------
// Name: IsUnreadMessages
// Desc: 
//------------------------------------------------------------------
bool UDPServer::IsUnreadMessages()
{
	bool queueIsEmpty = false;
	pthread_mutex_lock( &messageQueueMutex ); 

	if ( !clientMessageQueue.empty() ) {
		queueIsEmpty = true; 
	}

	pthread_mutex_unlock( &messageQueueMutex ); 

	return queueIsEmpty; 
}
//------------------------------------------------------------------
// Name: GetLatestMessage
// Desc: 
//------------------------------------------------------------------
void UDPServer::GetLatestMessage( ClientMessage* message )
{
	// wait until the listener thread is done with the queue 
	pthread_mutex_lock( &messageQueueMutex ); 

	if ( !clientMessageQueue.empty() ) {

        *message = clientMessageQueue.front(); 
		
		clientMessageQueue.pop(); 
	}

	pthread_mutex_unlock( &messageQueueMutex ); 
}
//---------------------------------------------------------------------------
// Name: ListenForMessage
// Desc:
//---------------------------------------------------------------------------
void UDPServer::ListenForMessage( void* threadId )
{
	struct sockaddr_in clientAddress; 
	char* messageBuffer = new char[MESSAGE_LENGTH]; 

	socklen_t sockLen = sizeof(clientAddress); 

	while ( 1 ) {

		// Check if we've been asked to quit
		pthread_mutex_lock( &listenerMutex ); 

		if ( stopListening ) {

			// make sure we release the mutex *before* we break out of the loop!
			pthread_mutex_unlock( &listenerMutex );
			break;  
		}

		pthread_mutex_unlock( &listenerMutex );

		printf("Server is Listening...\n");

		memset( (void*)messageBuffer, 0, MESSAGE_LENGTH ); 

		// don't lock until after we've received a message!
		// socket could be a different length when it comes back? 
		int receivedBytes = recvfrom( serverSocket, messageBuffer, MESSAGE_LENGTH, 0, (struct sockaddr*)&clientAddress, &sockLen ); 

		if ( receivedBytes == -1 ) {

			// error
			// help help help what do i do 

		} else {

			pthread_mutex_lock( &messageQueueMutex );
            
            ClientMessage clientMessage;
            
            clientMessage.address = clientAddress;
            memcpy( (void*)&clientMessage.message, (void*)messageBuffer, MESSAGE_LENGTH );

			// ClientMessage makes it's own copy of the messageBuffer
			clientMessageQueue.push( clientMessage );

			pthread_mutex_unlock( &messageQueueMutex );
		}
	}

	printf("Server listener is quitting.\n"); 

	delete messageBuffer; 

	pthread_exit(0); 
}
