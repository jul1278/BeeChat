// ServerChatConnection.h

#ifndef _SERVER_CHAT_CONNECTION_H
#define _SERVER_CHAT_CONNECTION_H

#include "BeeChatException.h"
#include "UDPServer.h"
// probably need other stuff

typedef unsigned int ClientID; 

// ServerChatConnection
class ServerChatConnection : public ChatConnection
{

private:
  
  std::queue<ClientMessage> messageQueue; 
  
  // stores the name of the new users
  std::queue<std::string> newUserQueue; 
  
  // at the lower level we're sending messages to clients through UDP
  std::map<ClientID, struct sockaddr_in> clientAddressMap; 
  
  // 
  UDPServer* udpServer; 
  
public: 
  
  ServerChatConnection()
  {
    // TODO: put try catch around here?
    this->udpServer = new UDPServer;   

  }
  ~ServerChatConnection(); 
  
  
  
  // 
  void Run()
  {
    if ( !udpServer->IsUnreadMessages() ) {
      return; 
    }
    
    ClientMessage message; 
    // 1. check our UDP connection to see if we've got any new messages
    //   get them all and store them in our message queue
    
    // 2. check if the sender address of the message is one we already know about
    // or if it's a new client that wants to join the server
    
    // 3. if we've got a new client add their socket to our map and generate a ClientID
    //    store the username in a queue as well
    udpServer->LatestMessage( &message );
    messageQueue.push(message); 
    
    struct sockaddr_in address = message.address; 
    
    // check if latest message sockaddr_in is in the map already
    std::map<ClientID, sockaddr_in>::const_iterator it = clientAddressMap.find(address); 
    
    if ( it == clientAddressMap.end() ) {
      // generate new ClientID
      ClientID newID = 4954545;
      
      clientAddressMap.insert( std::pair<ClientID, sockaddr_in>( newID, address  )); 
      
    }
    

    
    //  
    
    
  }
  
  bool IsNewClients(); 
  bool IsUnreadMessages(); 
  
  void GetLatestMessage( Message* message )
  {
    if ( !messageQueue.empty() ) {
      *message = messageQueue.front(); 
      messageQueue.pop(); 
    } 
  }
  ClientID GetLatestUser( std::string* username )
  {
    if ( !newUserQueue.empty()) {
      *newUser = newUserQueue.front(); 
      newUserQueue.pop(); 
    }
    
    ClientID newUserID = 
    
  }
  
  // send a message to someone
  void SendMessage( Message* message )
  {
    
  }
}; 

#endif
