// ServerChatConnection.cpp

#include "ConnectionLayer/ServerChatConnection.h"
#include "Message.h"


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
  // get all the messages from UDP
  while ( udpServer->IsUnreadMessages() ) {

    ClientMessage clientMessage; 

    udpServer->LatestMessage( &clientMessage ); 

    Message message; 

    memcpy( (void*)&message, (void*)&clientMessage.message, MESSAGE_SIZE ); 

    switch ( message.messageType ) {

      case LOGON_NOTIFY:
        ClientID clientID;
        clientID = this->LogonAddress( clientMessage.address ); 

        if ( clientID != 0 ) {
          LogonMessage* logonMessage = (LogonMessage*)message.messageData;
          logonMessage->clientID = clientID; 
          messageQueue.push(message); 
        }

      break;

      case LOGOFF_NOTIFY:
        this->LogoffAddress( clientMessage.address ); 
      break;  

      case PING_RESPONSE:
        // TODO: server shouldn't get these guys
      break;

      default:
        messageQueue.push(message);
      break; 

    }
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

  *message = messageQueue.front();
  messageQueue.pop(); 
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

    memset( (void*)&clientMessage, 0, sizeof(ClientMessage) );
    clientMessage.address = socketAddressDest;

    // DODGY FIX: sizeof(Message) instead of MESSAGE_SIZE
    memcpy( (void*)&clientMessage.message, (void*)message, sizeof(Message) );

    udpServer->SendMessage( &clientMessage );
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

        if ( memcmp( &it->second, &address, sizeof(struct sockaddr_in) ) == 0 ) {
            
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
ClientID ServerChatConnection::LogonAddress( struct sockaddr_in address )
{
    if ( this->IsAddressLoggedOn(address) == true ) {
        return 0;
    }

    ClientID clientID = clientAddressMap.size() + 1;

    clientAddressMap.insert( std::pair<ClientID, struct sockaddr_in>(clientID, address) );

    return clientID;
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

    if ( memcmp( &it->second, &address, sizeof(struct sockaddr_in )) == 0 ) {
      clientAddressMap.erase(it); 
      return; 
    }
  } 
}


