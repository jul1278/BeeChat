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
  
  SendMessage( Message* message );
  Message GetNewMessage(); 
};

// _CLIENT_H
#endif 
