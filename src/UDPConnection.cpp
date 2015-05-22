// UDPConnection.cpp
#include "UDPConnection.h"


//----------------------------------------------------------------------
// Name: UDPConnection
// Desc: 
//----------------------------------------------------------------------
UDPConnection::UDPConnection()
{
	pthread_mutex_init( &messageQueueMutex, NULL ); 
	pthread_mutex_init( &listenerThreadMutex, NULL ); 

	stopListening = false; 

	//listener = this;
}
//----------------------------------------------------------------------
// Name: ~UnreadConnection
// Desc: 
//----------------------------------------------------------------------
UDPConnection::~UDPConnection()
{
	pthread_mutex_destroy( &messageQueueMutex );
	pthread_mutex_destroy( &listenerThreadMutex ); 
}
//----------------------------------------------------------------------
// Name: Start
// Desc: 
//----------------------------------------------------------------------
void UDPConnection::Start()
{

	// check if a thread has already started
	stopListening = false; 
    
    
    
    //int res = pthread_create( &listenerThread, NULL, ListenerWrapper, NULL );
    
    //if ( res ) {
        // error
     //   std::cout << "pthread_error()" << std::endl;
    //}
}
//----------------------------------------------------------------------
// Name: Stop
// Desc: 
//----------------------------------------------------------------------
void UDPConnection::Stop()
{
	pthread_mutex_lock( &listenerThreadMutex ); 
	stopListening = true;
	pthread_mutex_unlock( &listenerThreadMutex );
    
    close(udpSocket);
    
	pthread_exit(NULL);
}
//----------------------------------------------------------------------
// Name: IsUnreadMessages
// Desc: 
//----------------------------------------------------------------------
bool UDPConnection::IsUnreadMessages()
{
	bool queueIsEmpty = false;
	pthread_mutex_lock( &messageQueueMutex ); 

	if ( messageQueue.empty() == false ) {
		// Don't return before we've unlocked the mutex
		queueIsEmpty = true; 
	}

	pthread_mutex_unlock( &messageQueueMutex ); 
	return queueIsEmpty; 
}
//----------------------------------------------------------------------
// Name: LatestMessage
// Desc: 
//----------------------------------------------------------------------
void UDPConnection::LatestMessage( ClientMessage* message )
{
	// wait until the listener thread is done with the queue 
	pthread_mutex_lock( &messageQueueMutex ); 

	if ( !messageQueue.empty() ) {
        
        memcpy( (void*)message, (void*)&messageQueue.front(), MESSAGE_LENGTH );
		messageQueue.pop(); 
	}

	pthread_mutex_unlock( &messageQueueMutex ); 
}
//----------------------------------------------------------------------
// Name: SendMessage
// Desc: 
//----------------------------------------------------------------------
void UDPConnection::SendMessage( ClientMessage* message )
{
	if ( sendto( udpSocket, message->message, MESSAGE_LENGTH, 0, (struct sockaddr*)&message->address, sizeof(struct sockaddr) ) == -1 ) {
		std::cout << "sendto() error" << std::endl; 
	} 
}
//---------------------------------------------------------------------------
// Name: ListenForMessage
// Desc:
//---------------------------------------------------------------------------
void* UDPConnection::ListenerThread( void* threadId )
{
	struct sockaddr_in senderAddress; 
	char messageBuffer[MESSAGE_LENGTH];

	socklen_t sockLen = sizeof(senderAddress); 

	while ( 1 ) {

		// Check if we've been asked to quit
		pthread_mutex_lock( &listenerThreadMutex ); 

		if ( stopListening ) {
			pthread_mutex_unlock( &listenerThreadMutex );
			break;  
		}

		pthread_mutex_unlock( &listenerThreadMutex );

		memset( (void*)messageBuffer, 0, MESSAGE_LENGTH ); 

		int receivedBytes = recvfrom( udpSocket, messageBuffer, MESSAGE_LENGTH, 0, (struct sockaddr*)&senderAddress, &sockLen ); 

		if ( receivedBytes == -1 ) {

			// error
			// help help help what do i do 

		} else {

			pthread_mutex_lock( &messageQueueMutex );
            
            ClientMessage clientMessage;  
            clientMessage.address = senderAddress;

            memcpy( (void*)&clientMessage.message, (void*)messageBuffer, MESSAGE_LENGTH );

			messageQueue.push( clientMessage );

			pthread_mutex_unlock( &messageQueueMutex );
		}
	}



	pthread_exit(0); 
}
