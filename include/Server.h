// Server.h
#ifndef _SERVER_H
#define _SERVER_H

#include <vector>

// Server
class Server
{
private:
  
  ServerChatConnection* chatConnection; 
  
  std::vector<User> users; 
  
public:
  
  Server();
  ~Server(); 
  
  void SendMessageToClient(  )
  Message GetNewMessage(); 
  
};


#endif
