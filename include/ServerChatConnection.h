// ServerChatConnection.h

#ifndef _SERVER_CHAT_CONNECTION_H
#define _SERVER_CHAT_CONNECTION_H

#include "BeeChatException.h"
#include "UDPServer.h"
// probably need other stuff



// ServerChatConnection
class ServerChatConnection : public ChatConnection
{

private:
  
  std::queue<Message> messageQueue; 
  std::queue<Users> newUserQueue; 
  
  // at the lower level we're sending messages to clients through UDP
  std::map<ClientAddress, ClientID> client; 
  
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
    // 1. check our UDP connection to see if we've got any new messages
    
    // 2. check if the sender address of the message is one we already know about
    // or if it's a new client that wants to join the server
    
    // 3. if we've got a new client add them on to our list
    // 
    
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
  void GetLatestUser( User* newUser )
  {
    if ( !newUserQueue.empty()) {
      *newUser = newUserQueue.front(); 
      newUserQueue.pop(); 
    }
  }
  
  // send a message to someone
  void SendMessage( Message* message )
  {
    
  }
}; 

#endif
