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
// Name: IsUnreadMessages
// Desc: 
//-------------------------------------------------------------------
bool ServerChatConnection::IsUnreadMessages()
{
  while ( udpServer->IsUnreadMessages() ) {

    ClientMessage clientMessage; 

    udpServer->LatestMessage( &clientMessage ); 

    Message message; 

    memcpy( (void*)&message, (void*)&clientMessage.message, MESSAGE_SIZE ); 

    switch ( message->messageType ) {

      case LOGON_NOTIFY:

        this->LogonAddress( clientMessage->address );  
      break;

      case LOGOFF_NOTIFY:
        this->LogoffAddress( clientMessage->address ); 
      break;  

      case PING_RESPONSE:
        // TODO: server shouldn't get these guys
      break;

    }

    // server wants the message anyway
    messageQueue.push(message); 
  }

  if ( messageQueue.empty() == false ) {
    return true;
  }
  return false; 
}
//-------------------------------------------------------------------
// Name: GetLatestMessage
// Desc: 
//-------------------------------------------------------------------
void ServerChatConnection::GetLatestMessage( Message* message)
{

  // are there any unread messages in our queue, not the UDP queue
  if ( this->IsUnreadMessages() == false ) {
    message = NULL;
    return;  
  } 

  (*message) = new Message(); 

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
void ServerChatConnection::SendMessageToClient( Message* message, ClientID clientID )
{
  // get the sockaddr_in from the map
  struct sockaddr_in socketAddressDest = clientAddressMap[clientID]; 

  ClientMessage clientMessage; 

  clientMessage.address = socketAddressDest; 

  if ( message->dataLength > MESSAGE_SIZE ) {
    // TODO: throw exception
    return; 
  }


  // DODGY FIX: sizeof(Message) instead of MESSAGE_SIZE
  memcpy( (void*)&clientMessage.message, (void*)message, sizeof(Message) ); 

  udpServer->SendMessage( &clientMessage ); 

}
//-------------------------------------------------------------------
// Name: IsNewClients
// Desc: 
//-------------------------------------------------------------------
bool ServerChatConnection::IsNewUser()
{
  return ( newUser.empty() == false ); 
}
//-------------------------------------------------------------------
// Name: GetNewestClient
// Desc: 
//-------------------------------------------------------------------
void ServerChatConnection::GetLatestUser( User* user )
{
	if ( this->IsNewUser() ) {
		*user = newUser.front(); 
		newUser.pop(); 
	}
}
//-------------------------------------------------------------------
// Name: IsAddressLoggedOn
// Desc:
//-------------------------------------------------------------------
bool ServerChatConnection::IsAddressLoggedOn( struct sockaddr_in address ) 
{
    // find address in the map otherwise add it
  std::map<ClientID, struct sockaddr_in>::iterator it; 

  for (  it = clientAddressMap.begin(); it != clientAddressMap.end(); it++ ) {

    if ( it->second() == address ) {

      // this address is already logged on
      return true; 
    }
  }

  return false; 
}
//-------------------------------------------------------------------
// Name: HandleLogonMessage
// Desc: 
//-------------------------------------------------------------------
void ServerChatConnection::LogonAddress( struct sockaddr_in address )
{
  if ( this->IsAddressLoggedOn(address) == true ) {
    return; 
  }

  ClientID clientID = clientAddressMap.size(); 

  clientAddressMap.insert( std::pair<clientID, address>() ); 
}
//-------------------------------------------------------------------
// Name: LogoffAddress
// Desc: 
//-------------------------------------------------------------------
void ServerChatConnection::LogoffAddress( struct sockaddr_in address ) 
{
      // find address in the map otherwise add it
  std::map<ClientID, struct sockaddr_in>::iterator it; 

  for (  it = clientAddressMap.begin(); it != clientAddressMap.end(); it++ ) {

    if ( it->second() == address ) {
      clientAddressMap.erase(it); 
      return; 
    }
  } 
}


