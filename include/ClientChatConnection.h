// ClientChatConnection.h

#ifndef _CLIENT_CHATCONNECTION_H
#define _CLIENT_CHATCONNECTION_H

class ClientChatConnection : public ChatConnection
{
  

  public:
    
    ClientChatConnection(); 
    ~ClientChatConnection(); 
    
  void ConnectToServer( std::string username );
  void Disconnect(); 
  
  void  SendMessageToServer( Message* message ); 
  bool IsUnreadMessages();   
  void GetLatestMessage( Message* message ); 
}; 


#endif
