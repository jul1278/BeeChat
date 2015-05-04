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
  
  const int serverPort = 6969; 
  
  ServerChatConnection* chatConnection; 
  
  // we know about users - each user stores a clientID 
  // client ID maps to a client address inside chatconnection
  std::vector<User> users; 
  
  std::queue<Message> messageQueue; 
  
public:
  
  //---------------------------------------------------------------------------------
  // Name: Server
  // Desc:
  //---------------------------------------------------------------------------------
  Server()
  {
    TryStart(); 
  }
  //---------------------------------------------------------------------------------
  // Name: TryStart
  // Desc:
  //---------------------------------------------------------------------------------
  ~Server()
  {
    // TODO: tell chat connection that i'm quitting
    
    delete chatConnection; 
  }
  //---------------------------------------------------------------------------------
  // Name: TryStart
  // Desc:
  //---------------------------------------------------------------------------------
  bool TryStart()
  {
    // try to start a server
    return( chatConnection->StartServer() );
  }
  //---------------------------------------------------------------------------------
  // Name: IsActive
  // Desc:
  //---------------------------------------------------------------------------------
  bool IsActive()
  {
    // did i successfully start? 
    return true; 
    // else
    
    return false; 
    
  }
  //---------------------------------------------------------------------------------
  // Name: Run
  // Desc:
  //---------------------------------------------------------------------------------
  int Run() 
  {
    // have we recieved any messages on the chat connection? 
    
    // do we need to relay messages back to clients
    
    //chatConnection->SendToAllClients( newMessage ); 
    
  }
  
};


#endif
