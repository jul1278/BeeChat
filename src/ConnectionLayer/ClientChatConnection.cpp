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
void ClientChatConnection::Connect( std::string username )
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

		udpClient->LatestMessage( &message ); 

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
void ClientChatConnection::GetLatestMessages( UserMessage** message )
{
	if ( this->IsUnreadMessages() ) {

		(*message) = new UserMessage(); 

		(*message)->messageData = new byte[MESSAGE_SIZE]; 
		memcpy( (void*)(*message)->messageData, (void*)&messageQueue.front().message, MESSAGE_SIZE ); 
		(*message)->dataLength = MESSAGE_SIZE; 

	} else {
		*message = NULL; 
	}
}
//---------------------------------------------------------------------
// Name: SendMessage
// Desc:
//---------------------------------------------------------------------
void ClientChatConnection::SendMessage( UserMessage* message )
{
	char* messageData = new char[MESSAGE_SIZE]; 
	memcpy( (void*)messageData, (void*)message->messageData, message->dataLength ); 

	udpClient->SendMessage( messageData ); 

	delete messageData; 

}

  