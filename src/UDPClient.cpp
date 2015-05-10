// UDPClient.cpp
#include "UDPClient.h"

UDPClient* listenerClient; 

void* UDPClientListener(void* threadId)
{
	listenerClient->ListenForMessage(threadId);
    return NULL; 
}

//------------------------------------------------------------------
// Name: UDPClient
// Desc: 
//------------------------------------------------------------------
UDPClient::UDPClient()
{

	hostent* pHost; 
	pHost = (hostent*) gethostbyname( (char*) "localhost" ); 

	// htonl and htons convert ints into 'network representations'
	serverAddress.sin_family = AF_INET; 
	serverAddress.sin_addr.s_addr = *((in_addr_t*)pHost->h_addr); 
	serverAddress.sin_port = htons(PORT); 

	pthread_mutex_init( &messageQueueMutex, NULL ); 
	pthread_mutex_init( &listenerMutex, NULL ); 

	// can i do this?
	listenerClient = this; 

}
//------------------------------------------------------------------
// Name: ~UDPClient
// Desc: 
//------------------------------------------------------------------
UDPClient::~UDPClient()
{
	pthread_mutex_destroy( &messageQueueMutex );
	pthread_mutex_destroy( &listenerMutex ); 
}
//------------------------------------------------------------------
// Name: StartClient
// Desc: 
//------------------------------------------------------------------
void UDPClient::StartClient()
{

	printf("Started client.\n");
	

	// get a socket
	clientSocket = socket( AF_INET, SOCK_DGRAM, 0 ); 

	if ( clientSocket == -1 ) {
		std::cout << "socket() error" << std::endl;  
	}

	// check if a thread has already started
	stopListening = false; 

	long threadId = 0; 

	

	int res = pthread_create( &listenerThread, NULL, UDPClientListener, NULL ); 

	if ( res ) {
		// error
		std::cout << "pthread_error()" << std::endl; 
	}
}
//------------------------------------------------------------------
// Name: StopClient
// Desc: 
//------------------------------------------------------------------
void UDPClient::StopClient()
{

	pthread_mutex_lock( &listenerMutex ); 
	stopListening = true;
	pthread_mutex_unlock( &listenerMutex ); 

	// is it safe to just exit now?

	// close socket
	close( clientSocket ); 
	pthread_exit(NULL); 
	
}
//------------------------------------------------------------------
// Name: SendToServer
// Desc: 
//------------------------------------------------------------------
void UDPClient::SendToServer( char* message )
{
	//TODO: are we sure a server exists? 

	if ( sendto( clientSocket, message, MESSAGE_LENGTH, 0, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr) ) == -1 ) {
		std::cout << "sendto() error" << std::endl; 
	} 
}
//------------------------------------------------------------------
// Name: IsUnreadMessages
// Desc: 
//------------------------------------------------------------------
bool UDPClient::IsUnreadMessages()
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
// Name: GetLatestMessages
// Desc: messages are always  
//------------------------------------------------------------------
void UDPClient::GetLatestMessage(ClientMessage* clientMessage)
{
	// wait until the listener thread is done with the queue 
	pthread_mutex_lock( &messageQueueMutex ); 

	if ( !clientMessageQueue.empty() ) {
        
        *clientMessage = clientMessageQueue.front(); 
        
		clientMessageQueue.pop(); 
	}

	pthread_mutex_unlock( &messageQueueMutex ); 
}
//---------------------------------------------------------------------------
// Name: ListenForMessage
// Desc:
//---------------------------------------------------------------------------
void UDPClient::ListenForMessage( void* threadId )
{
	struct sockaddr_in serverAddress; 
	char* messageBuffer = new char[MESSAGE_LENGTH];
	socklen_t sockLen = sizeof(serverAddress);   

	while ( 1 ) {

		// Check if we've been asked to quit
		pthread_mutex_lock( &listenerMutex ); 

		if ( stopListening ) {

			pthread_mutex_unlock( &listenerMutex );

			break;  
		}

		pthread_mutex_unlock( &listenerMutex );

		memset( (void*)messageBuffer, 0, MESSAGE_LENGTH ); 

		printf("Client is Listening...\n");

		// don't lock until after we've received a message!
		// socket could be a different length when it comes back? 
		int receivedBytes = recvfrom( clientSocket, messageBuffer, MESSAGE_LENGTH, 0, (struct sockaddr*)&serverAddress, &sockLen ); 
		

		if ( receivedBytes == -1 ) {
			// error
			// help help help what do i do 

		} else {

			pthread_mutex_lock( &messageQueueMutex ); 
			
			// ClientMessage makes it's own copy of the messageBuffer
            // obviously the message came from a server so is this necessary?
            ClientMessage clientMessage;
            
            clientMessage.address = serverAddress;
            
            memcpy( (void*)&clientMessage.message, (void*)messageBuffer, MESSAGE_LENGTH );
            
			clientMessageQueue.push( clientMessage );
			pthread_mutex_unlock( &messageQueueMutex );

		}
	}

	printf("Client listener is quitting.\n");

	delete messageBuffer; 

	pthread_exit(0); 
}


