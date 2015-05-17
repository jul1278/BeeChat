// Client.cpp
#include "Client.h"
#include "Message.h"

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

	if ( username.length() > MAX_USERNAME_CHAR ) {

		// throw exception "Username exceeds MAX_USERNAME_CHAR"
		return; 
	}

	// Create a new message
	// make our desired username the data of the message
	// send
    byte* data = new byte[username.length()];
    memcpy( (void*)data, (void*)&username.c_str(), username.length() );
    
    
	Message message; 
	LogonMessage logonMessage;  
 	
	message.messageType = LOGON_NOTIFY; 
	message.messageData = &logonMessage; 

	memcpy( (void*)&logonMessage.username, (void*)username.c_str(), username.length() ); 

	logonMessage.usernameColor = 0x00; 


	chatConnection->SendMessageToServer( &message ); 
}
//-------------------------------------------------------------------
// Name: Disconnet
// Desc: 
//-------------------------------------------------------------------
void Client::Disconnect()
{
	// TODO: implement message types and send a logoff notification
	//       we should be able to do something like message = messageFactory->ConstructMessage( LOGOFF_NOTIFY ) 
}
//-------------------------------------------------------------------
// Name: PassMessage
// Desc: ay pass me the message bro
//-------------------------------------------------------------------
void Client::PassMessage( Message* message )
{
	// TODO: implement message types and decide what to do with message
	chatConnection->SendMessageToServer( message );   
}
//-------------------------------------------------------------------
// Name: GetLatestMessage
// Desc: 
//-------------------------------------------------------------------
void Client::GetLatestMessage( Message* message )
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