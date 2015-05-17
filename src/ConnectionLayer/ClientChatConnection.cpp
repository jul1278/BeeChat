// ClientChatConnection.cpp
// Julian Pattie

#include "ClientChatConnection.h"

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
		
		ClientMessage clientMessage; 
		Message message;
		udpClient->LatestMessage( &clientMessage ); 
		memcpy( (void*)&message.messageData, (void*) clientMessage.message, MESSAGE_SIZE ); 

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
void ClientChatConnection::GetLatestMessage( Message* message )
{
	if ( this->IsUnreadMessages() ) {

		memcpy( (void*)message->messageData, (void*)&messageQueue.front().message, MESSAGE_SIZE ); 

	} else {
		message = NULL; 
	}
}
//---------------------------------------------------------------------
// Name: SendMessage
// Desc:
//---------------------------------------------------------------------
void ClientChatConnection::SendMessageToServer( Message* message )
{
	ClientMessage clientMessage; 
	clientMessage.address = 0; // we know where the server is 
	memcpy( (void*)&clientMessage.messageData, (void*)message->messageData, MESSAGE_SIZE ); 

	udpClient->SendMessage( messageData ); 
}

  