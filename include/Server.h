// Server.h
#ifndef _SERVER_H
#define _SERVER_H

#include <list>
#include "User.h"
#include "MessageFactory.h"
#include "ServerChatConnection.h"


// Server
class Server
{
private:

  
   class ServerChatConnection* chatConnection; 
  
  // we know about users - each user stores a clientID 
  // client ID maps to a client address inside chatconnection
  std::list<struct User> users; 
  
  std::queue<struct Message> inMessageQueue;
  std::queue<struct Message> outMessageQueue;  
  
  void HandleLogonMessage(struct Message* message); 
  void HandleLogoffMessage(struct Message* message); 
  void HandleChatMessage(struct Message* message);

public:

  Server();
  ~Server();

  bool Connect();
  void Disconnect(); 
  bool IsActive(); 

  int Run();

};


#endif
