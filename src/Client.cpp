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
    chatConnection->Connect();
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
void Client::Connect( std::string username, byte usernameColor )
{
    
	if ( username.length() > MAX_NUM_USERNAME_CHAR ) {

		return; 
	}

	// Create a new message
	// make our desired username the data of the message
	// send    
	Message message;  
	LogonMessage* logonMessage = (LogonMessage*) message.messageData;
 	
	message.messageType = LOGON_NOTIFY; 
	memcpy( (void*)&logonMessage->username, (void*)username.c_str(), username.length() ); 

	logonMessage->usernameColor = usernameColor; 
	logonMessage->textColor = 0x00; 

	chatConnection->SendMessageToServer( &message ); 
}
//-------------------------------------------------------------------
// Name: Disconnet
// Desc: 
//-------------------------------------------------------------------
void Client::Disconnect()
{
	chatConnection->Disconnect(); 

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


	// TODO: may need to handle some message types here

	if ( this->IsUnreadMessage() ) {

		*message = messageQueue.front();
		messageQueue.pop(); 

		return; 
	} else {
		message = NULL; 
	}	
}
//-------------------------------------------------------------------
// Name: IsNewMessage
// Desc: 
//-------------------------------------------------------------------
bool Client::IsUnreadMessage()
{
    while ( chatConnection->IsUnreadMessages() ) {
        
        Message newMessage;
        
        chatConnection->GetLatestMessage( &newMessage );
        messageQueue.push( newMessage );
    }

	return( messageQueue.empty() == false ); 
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