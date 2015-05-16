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
}
//---------------------------------------------------------------------
// Name: Disconnect
// Desc:
//---------------------------------------------------------------------
void ClientChatConnection::Disconnect()
{
}
//---------------------------------------------------------------------
// Name: IsUnreadMessages
// Desc:
//---------------------------------------------------------------------
bool ClientChatConnection::IsUnreadMessages()
{
}
//---------------------------------------------------------------------
// Name: GetLatestMessages
// Desc:
//---------------------------------------------------------------------
void ClientChatConnection::GetLatestMessages( UserMessage** message )
{
}
//---------------------------------------------------------------------
// Name: SendMessage
// Desc:
//---------------------------------------------------------------------
void ClientChatConnection::SendMessage( UserMessage* message )
{
	
}

  