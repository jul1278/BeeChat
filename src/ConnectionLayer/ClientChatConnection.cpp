// ClientChatConnection.cpp
// Julian Pattie

#include "ConnectionLayer/ClientChatConnection.h"

//---------------------------------------------------------------------
// Name: ClientChatConnection
// Desc:
//---------------------------------------------------------------------
ClientChatConnection::ClientChatConnection()
{
	this->udpClient = new UDPClient(); 	
}
//---------------------------------------------------------------------
// Name: ~ClientChatConnection
// Desc:
//---------------------------------------------------------------------
ClientChatConnection::~ClientChatConnection()
{
	delete this->udpClient; 
}
//---------------------------------------------------------------------
// Name: Connect
// Desc:
//---------------------------------------------------------------------
void ClientChatConnection::Connect()
{
	udpClient->Start(); 
}
//---------------------------------------------------------------------
// Name: Disconnect
// Desc:
//---------------------------------------------------------------------
void ClientChatConnection::Disconnect()
{
	udpClient->Stop(); 
}
//---------------------------------------------------------------------
// Name: IsUnreadMessages
// Desc:
//---------------------------------------------------------------------
bool ClientChatConnection::IsUnreadMessages()
{
	// get unread messages from UDP first
	while ( udpClient->IsUnreadMessages() ) {
		
		struct ClientMessage clientMessage; 
		Message message;
		udpClient->LatestMessage( &clientMessage ); 
		memcpy( (void*)&message, (void*) clientMessage.message, MESSAGE_SIZE ); 

		// we dont't care about the clientID

		messageQueue.push( message ); 
	}

	if ( messageQueue.empty() == false ) {
		return true;
	}

	return false; 
}
//---------------------------------------------------------------------
// Name: GetLatestMessages
// Desc:
//---------------------------------------------------------------------
void ClientChatConnection::GetLatestMessage( struct Message* message )
{
	if ( this->IsUnreadMessages() ) {

		*message = messageQueue.front(); 
		messageQueue.pop(); 

	} else {
		message = NULL; 
	}
}
//---------------------------------------------------------------------
// Name: SendMessage
// Desc:
//---------------------------------------------------------------------
void ClientChatConnection::SendMessageToServer( struct Message* message )
{
	struct ClientMessage clientMessage;
    
    // we need to put the whole message in
	memcpy( (void*)&clientMessage.message, (void*)message, MESSAGE_SIZE );
	udpClient->SendToServer( clientMessage.message );
}

  