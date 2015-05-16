// ServerChatConnection.cpp

#include "ServerChatConnection.h"


//-------------------------------------------------------------------
// Name: ServerChatConnection
// Desc: 
//-------------------------------------------------------------------
ServerChatConnection::ServerChatConnection()
{
  this->udpServer = new UDPServer(); 
}
//-------------------------------------------------------------------
// Name: ~ServerChatConnection
// Desc: 
//-------------------------------------------------------------------
ServerChatConnection::~ServerChatConnection()
{
  delete this->udpServer; 
}
//-------------------------------------------------------------------
// Name: Connect
// Desc: 
//-------------------------------------------------------------------
void ServerChatConnection::Connect()
{
  udpServer->Start();  
}
//-------------------------------------------------------------------
// Name: Disconnect
// Desc: 
//-------------------------------------------------------------------
void ServerChatConnection::Disconnect()
{
  udpServer->Stop(); 
}
//-------------------------------------------------------------------
// Name: Run	
// Desc: 
//
// 1. check our UDP connection to see if we've got any new messages
//    get them all and store them in our message queue
//
// 2. check if the sender address of the message is one we already know about
//    or if it's a new client that wants to join the server
//
// 3. if we've got a new client add their socket to our map and generate a ClientID
//    store the username in a queue as well
//-------------------------------------------------------------------
void ServerChatConnection::Run()
{
    if ( udpServer->IsUnreadMessages() == true ) {
      // get the messages
    }
    
    Message = 

    ClientMessage message; 


    struct sockaddr_in address = message.address; 
    
    // check if latest message sockaddr_in is in the map already
    std::map<ClientID, sockaddr_in>::const_iterator it = clientAddressMap.find(address); 
    if ( it == clientAddressMap.end() ) {
      // generate new ClientID
      ClientID newID = 4954545;
      
      clientAddressMap.insert( std::pair<ClientID, sockaddr_in>( newID, address  )); 
      
    }
    
}
//-------------------------------------------------------------------
// Name: IsUnreadMessages
// Desc: 
//-------------------------------------------------------------------
bool ServerChatConnection::IsUnreadMessages()
{
  if ( messageQueue.empty() == false ) {
    return true;
  }
  return false; 
}
//-------------------------------------------------------------------
// Name: GetLatestMessage
// Desc: 
//-------------------------------------------------------------------
void ServerChatConnection::GetLatestMessage( UserMessage** message)
{

  // are there any unread messages in our queue, not the UDP queue
  if ( this->IsUnreadMessages() == false ) {
    *message = NULL;
    return;  
  } 

  (*message) = new UserMessage(); 

  // refactor this into a function
  std::map<ClientID, struct sockaddr_in>::iterator it = clientAddressMap.begin(); 

  for ( it  = clientAddressMap.begin(); it != clientAddressMap.end(); it++ ) {

    // Get the client ID of the most recently received message
    if ( messageQueue.front() == it->second ) {

      (*message)->sender.clientID = it->first;
      break; 
    }  
  } 

  // copy the actual message data
  (*message)->messageData = new byte[MESSAGE_SIZE];
  memcpy( (void*)(*message)->messageData, (void*)&messageQueue.front().message, MESSAGE_SIZE ); 

  (*message).dataLength = MESSAGE_SIZE; 
  (*message).dest = NULL; 
  
  return; 

}
//-------------------------------------------------------------------
// Name: SendMessage
// Desc: 
//-------------------------------------------------------------------
void ServerChatConnection::SendMessage( UserMessage* message)
{
  // get the sockaddr_in from the map
  struct sockaddr_in socketAddressDest = clientAddressMap[message->dest.clientID]; 

  ClientMessage clientMessage; 

  clientMessage.address = socketAddressDest; 

  if ( message->dataLength > MESSAGE_SIZE ) {
    // TODO: throw exception
    return; 
  }

  memcpy( (void*)&clientMessage.address, (void*)message->messageData, message->dataLength ); 

  udpServer->SendMessage( &clientMessage ); 

}
//-------------------------------------------------------------------
// Name: IsNewClients
// Desc: 
//-------------------------------------------------------------------
bool ServerChatConnection::IsNewUser()
{
	if ( newUser.empty() == false ) {
		return true; 
	}

	return true;
}
//-------------------------------------------------------------------
// Name: GetNewestClient
// Desc: 
//-------------------------------------------------------------------
void ServerChatConnection::GetLatestUser( User* user )
{
	if ( this->IsNewClients() ) {
		*user = newUser.front(); 

		newUser.pop(); 
	}
}
