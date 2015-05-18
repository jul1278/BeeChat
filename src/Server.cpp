// Server.cpp
#include "Server.h"
#include "Message.h"

//---------------------------------------------------------------------------------
// Name: Server
// Desc:
//---------------------------------------------------------------------------------
Server::Server()
{
	chatConnection = new ServerChatConnection(); 
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
bool Server::Connect()
{
    // try to start a server
    chatConnection->Connect();

    // FIX ME
    return( true );	
}
//---------------------------------------------------------------------------------
// Name: Disconnect
// Desc:
//---------------------------------------------------------------------------------
void Server::Disconnect()
{
	chatConnection->Disconnect(); 
}
//---------------------------------------------------------------------------------
// Name: IsActive
// Desc:
//---------------------------------------------------------------------------------
bool Server::IsActive()
{
    return false;
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

		chatConnection->GetLatestMessage( &message ); 

		switch ( message.messageType ) {
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
	while ( outMessageQueue.empty() != true ) {

		std::list<User>::iterator usersIt; 

		for ( usersIt = users.begin(); usersIt != users.end(); usersIt++ ) {

			Message message = outMessageQueue.front(); 

			chatConnection->SendMessageToClient( &message, usersIt->clientID ); 
		}
        
        outMessageQueue.pop(); 
	}
    
    return 0; 
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

    Message alertMessage;
    ChatMessage* chatMessage = (ChatMessage*)alertMessage.messageData;
    
    std::string alertMessageString( user.username );
    alertMessageString += " has logged on.";
    
    memcpy( (void*)chatMessage->messageText, (void*)alertMessageString.c_str(), alertMessageString.length() );
    
	// TODO: message alert "user has logged on."
    outMessageQueue.push( alertMessage );
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

	std::list<User>::iterator it; 

	// might be a more stl way of doing this
	for ( it = users.begin(); it != users.end(); it++ ) {
		if ( it->clientID == logoffMessage->clientID ) {
			users.erase(it); 
			break; 
		}
	}

    Message alertMessage;
    ChatMessage* chatMessage = (ChatMessage*)alertMessage.messageData;
    
    std::string alertMessageString( it->username );
    alertMessageString += " has logged off.";
    
    memcpy( (void*)chatMessage->messageText, (void*)alertMessageString.c_str(), alertMessageString.length() );
    
    // TODO: message alert "user has logged on."
    outMessageQueue.push( alertMessage );
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

