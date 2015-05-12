// ServerChatConnection.h

#ifndef _SERVER_CHAT_CONNECTION_H
#define _SERVER_CHAT_CONNECTION_H

#include "BeeChatException.h"
// probably need other stuff

class ServerChatConnection : public ChatConnection
{

private:
  
  std::vector<User> user; 
  
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
    // check our UDP connection to see if we've got any new messages
    
    // check if the sender address of the message is one we already know about
    // or if it's a new client that wants to join the server
  }

  // send a message to someone
  void SendMessage( Message* message ); 

  
}; 

#endif
