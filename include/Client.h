// Client.h

#ifndef _CLIENT_H
#define _CLIENT_H

// Client
class Client
{
private:
  
  ClientChatConnection* chatConnection; 
  
public:

  Client();
  ~Client(); 
  
  // do we need this?
  int ConnectionStatus(); 
  
  // if not connected throw SendMessageException
  int SendMessage( Message* message );
  
  bool IsUnreadMessages(); 
  
  Message GetNewMessage(); 
};

// _CLIENT_H
#endif 
