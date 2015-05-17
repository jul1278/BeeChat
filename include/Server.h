// Server.h
#ifndef _SERVER_H
#define _SERVER_H

#include <vector>
#include "User.h"
#include "MessageFactory.h"

// Server
class Server
{
private:

  
  ServerChatConnection* chatConnection; 
  
  // we know about users - each user stores a clientID 
  // client ID maps to a client address inside chatconnection
  std::vector<User> users; 
  
  std::queue<Message> messageQueue; 
  
public:

  Server();
  ~Server();

  bool Connect();
  void Disconnect(); 
  bool IsActive(); 

  int Run();

};


#endif
