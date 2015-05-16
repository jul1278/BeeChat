// ServerChatConnection.h

#ifndef _SERVER_CHAT_CONNECTION_H
#define _SERVER_CHAT_CONNECTION_H

#include "IChatConnection.h"
#include "BeeChatException.h"
#include "UDPServer.h"
#include "User.h"

// probably need other stuff
typedef unsigned int ClientID; 

// ServerChatConnection
class ServerChatConnection : public IChatConnection
{

private:

  // stores the name of the new users
  std::queue<User> newUserQueue; 

  // message queue
  std::queue<ClientMessage>
  
  // at the lower level we're sending messages to clients through UDP
  std::map<ClientID, struct sockaddr_in> clientAddressMap;

  UDPServer* udpServer;  
    
public: 

  ServerChatConnection();
  ~ServerChatConnection(); 

  void Connect();
  void Disconnect();  

  void Run(); 

  bool IsUnreadMessages(); 
  void GetLatestMessage(UserMessage** message); 

  void SendMessage(UserMessage* message); 
  
  bool IsNewUser(); 
  void GetLatestUser(User* user); 
}; 

#endif
