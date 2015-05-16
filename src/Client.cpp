// Client.cpp
#include "Client.h"

//-------------------------------------------------------------------
// Name: Client
// Desc: 
//-------------------------------------------------------------------
Client::Client()
{
	this->chatConnection = new ClientChatConnection(); 
}
//-------------------------------------------------------------------
// Name: ~Client
// Desc: 
//-------------------------------------------------------------------
Client::~Client()
{
	delete chatConnection; 
}
//-------------------------------------------------------------------
// Name: Connect
// Desc: 
//-------------------------------------------------------------------
void Client::Connect( std::string username )
{
	// Create a new message
	// make our desired username the data of the message
	// send
    byte* data = new byte[username.length()];
    memcpy( (void*)data, (void*)&username.c_str(), username.length() );
    
    
	UserMessage logonMessage( data, username.length() );
	chatConnection->SendMessageToServer( &logonMessage ); 
}
//-------------------------------------------------------------------
// Name: Disconnet
// Desc: 
//-------------------------------------------------------------------
void Client::Disconnect()
{
	// TODO: implement message types and send a logoff notification
}
//-------------------------------------------------------------------
// Name: PassMessage
// Desc: ay pass me the message bro
//-------------------------------------------------------------------
void Client::PassMessage( UserMessage* message )
{
	// TODO: implement message types and decide what to do with message
	chatConnection->SendMessageToServer( message );   
}
//-------------------------------------------------------------------
// Name: GetLatestMessage
// Desc: 
//-------------------------------------------------------------------
void Client::GetLatestMessage( UserMessage* message )
{
	while ( chatConnection->IsUnreadMessages() ) {

		UserMessage* newMessage;  
		chatConnection->GetLatestMessage( &newMessage );
		userMessageQueue.push( *newMessage );

		// do we need to delete newMessage? or does its destructor get called when it goes out of scope?
		delete newMessage; 
	}

	// TODO: implement message types and message handling logic...

	if ( this->IsUnreadMessages() ) {
		*message = userMessageQueue.front();
		userMessageQueue.pop(); 
	}

	message = NULL;
}
//-------------------------------------------------------------------
// Name: IsNewActiveUserList
// Desc: 
//-------------------------------------------------------------------
bool Client::IsNewActiveUserList()
{
	//TODO: actually implement this
	return false; 
}
//-------------------------------------------------------------------
// Name: GetLatestActiveUserList
// Desc: 
//-------------------------------------------------------------------
void Client::GetLatestActiveUserList()
{
}