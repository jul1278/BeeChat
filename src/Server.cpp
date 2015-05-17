// Server.cpp
#include "Server.h"

//---------------------------------------------------------------------------------
// Name: Server
// Desc:
//---------------------------------------------------------------------------------
Server::Server()
{
	chatConnection = new UDPChatConnection(); 
}
//---------------------------------------------------------------------------------
// Name: ~Server
// Desc:
//---------------------------------------------------------------------------------
Server::~Server()
{
	delete chatConnection; 
}
//---------------------------------------------------------------------------------
// Name: TryConnect
// Desc:
//---------------------------------------------------------------------------------
bool Connect()
{
    // try to start a server
    chatConnection->StartServer();

    // FIX ME
    return( true );	
}
//---------------------------------------------------------------------------------
// Name: Disconnect
// Desc:
//---------------------------------------------------------------------------------
void Disconnect()
{
	chatConnection->Disconnect(); 
}
//---------------------------------------------------------------------------------
// Name: IsActive
// Desc:
//---------------------------------------------------------------------------------
bool IsActive()
{
}
//---------------------------------------------------------------------------------
// Name: Server
// Desc:
//---------------------------------------------------------------------------------
int Server::Run()
{
	// check if we've recieved any messages
	while ( chatConnection->IsUnreadMessages() == true ) {

		Message message; 

		chatConnection->GetUnreadMessage( &message ); 

		switch ( message->messageType ) {
			case LOGON_NOTIFY:
				this->HandleLogonMessage( &message ); 
			break; 
			case LOGOFF_NOTIFY:
				this->HandleLogoffMessage(&message);
			break; 
			case CHAT_MESSAGE:
				this->HandleChatMessage(&message);
			break; 
		}
	}

	// relay chat messages back to users
}
//---------------------------------------------------------------------------------
// Name: HandleLogon
// Desc:
//---------------------------------------------------------------------------------
void Server::HandleLogonMessage(Message* message)
{
	if ( message->messageType != LOGON_NOTIFY ) {
		return; 
	}

	LogonMessage* logonMessage = (LogonMessage*) &message->messageData;

	User user; 

	user.clientID = logonMessage->clientID; 
	user.usernameColor = logonMessage->usernameColor; 
	user.textColor = logonMessage->textColor; 
	user.username = std::string( logonMessage->username ); 

	users.push_back( user ); 


	// TODO: message alert "User has logged on."
}
//---------------------------------------------------------------------------------
// Name: HandleLogoff
// Desc:
//---------------------------------------------------------------------------------
void Server::HandleLogoffMessage(Message* message)
{
	if ( message->messageType != LOGOFF_NOTIFY ) {
		return; 
	}

	LogoffMessage* logoffMessage = (LogoffMessage*) message->messageData; 

	std::vector<User>::iterator it; 

	// might be a more stl way of doing this
	for ( it == users.begin(); it != users.end(); it++ ) {
		if ( it->clientID == logoffMessage->clientID ) {
			users(it).erase(); 
			break; 
		}
	}

	// TODO: message alert "User has logged off."
}
//---------------------------------------------------------------------------------
// Name: HandleChatMessage
// Desc:
//---------------------------------------------------------------------------------
void Server::HandleChatMessage(Message* message)
{
	if ( message->messageType != CHAT_MESSAGE ) {
		return; 
	}

	outMessageQueue.push( *message );
}

