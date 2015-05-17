// Server.h
#ifndef _SERVER_H
#define _SERVER_H

#include <list>
#include "User.h"
#include "MessageFactory.h"
#include "ConnectionLayer/ServerChatConnection.h"


// Server
class Server
{
private:

  
  ServerChatConnection* chatConnection; 
  
  // we know about users - each user stores a clientID 
  // client ID maps to a client address inside chatconnection
  std::list<User> users; 
  
  std::queue<Message> inMessageQueue;
  std::queue<Message> outMessageQueue;  
  
  void HandleLogonMessage(Message* message); 
  void HandleLogoffMessage(Message* message); 
  void HandleChatMessage(Message* message);

public:

  Server();
  ~Server();

  bool Connect();
  void Disconnect(); 
  bool IsActive(); 

  int Run();

};


#endif
