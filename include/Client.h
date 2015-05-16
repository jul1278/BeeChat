// Client.h

#ifndef _CLIENT_H
#define _CLIENT_H

#include "UserMessage.h"
#include "User.h"
#include "ClientChatConnection.h"

// Client
class Client
{
private:
  
  std::queue<UserMessage> userMessageQueue; 

  ClientChatConnection* chatConnection; 
  


public:

  Client();
  ~Client(); 
  
  // do we need this?
  int ConnectionStatus(); 

  void Connect( std::string userName );
  void Disconnect(); 
  
  // if not connected throw SendMessageException
  int PassMessage( Message* message );
  
  bool IsUnreadMessages();   
  void GetLatestMessage(UserMessage* message); 

  bool IsNewActiveUserList();
  void GetLatestActiveUserList(); 


};

// _CLIENT_H
#endif 
