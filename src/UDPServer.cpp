// UDPServer.cpp
#include <UDPServer.h>

//------------------------------------------------------------------
// Name: UDPServer
// Desc: 
//------------------------------------------------------------------
UDPServer::UDPServer()
{
	serverAddress.sin_family = AF_INET; 	
	serverAddress.sin_addr.s_addr = INADDR_ANY; 
	serverAddress.sin_port = htons(port); 
}
//------------------------------------------------------------------
// Name: ~UDPServer
// Desc: 
//------------------------------------------------------------------
UDPServer::~UDPServer()
{
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

		//std::cout << "socket() error" << std::endl; 
		// error throw exception
		return false; 
	}

	// difference between client and server is that a server's socket is bound to a port
	// once this port has been bound to then you can't bind to it until it gets released
	if ( bind( serverSocket, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr) ) == -1 ) {

		// did we error because the port has already been bound or something else
		return false; 
	}

	return true;
}
//------------------------------------------------------------------
// Name: StopServer
// Desc: 
//------------------------------------------------------------------
void UDPServer::StopServer()
{
	// what do
	close(serverSocket);
}
//------------------------------------------------------------------
// Name: SendToClient
// Desc: 
//------------------------------------------------------------------
void UDPServer::SendToClient( ClientMessage* ClientMessage )
{
	// TODO: check if we're a legit server at the moment

	// TODO: should be "sizeof(struct sockaddr)" or "sizeof(clientAddress)" ???
	int res = sendto( serverSocket, clientMessage->message, MESSAGE_LENGTH, 0, (struct sockaddr*)clientMessage->address, sizeof(struct sockaddr) ); 

	if ( res  == -1 ) {
		// error what do 
	}
}
//------------------------------------------------------------------
// Name: IsUnreadMessages
// Desc: 
//------------------------------------------------------------------
bool UDPServer::IsUnreadMessages()
{
	pthread_mutex_lock( &messageQueueMutex ); 

	if ( !messageQueue.empty() ) {
		return true; 
	}

	return false; 

	pthread_mutex_unlock( &messageQueueMutex ); 
}
//------------------------------------------------------------------
// Name: GetLatestMessage
// Desc: 
//------------------------------------------------------------------
void UDPServer::GetLatestMessage( ClientMessage* message )
{
	// wait until the listener thread is done with the queue 
	pthread_mutex_lock( &messageQueueMutex ); 

	if ( !messageQueue.empty() ) {

		memcpy( (void*)messageQueue, (void*)messageQueue.front(), MESSAGE_LENGTH ); 
		messageQueue.pop(); 
	}

	pthread_mutex_unlock( &messageQueueMutex ); 
}
//---------------------------------------------------------------------------
// Name: ListenForMessage
// Desc:
//---------------------------------------------------------------------------
void* UDPServer::ListenForMessage( void* threadId )
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
