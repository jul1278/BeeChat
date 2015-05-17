// Client.h

#ifndef _CLIENT_H
#define _CLIENT_H

#include "Message.h"
#include "User.h"
#include "ConnectionLayer/ClientChatConnection.h"

// Client
class Client
{
private:
  
    std::queue<Message> messageQueue;
    ClientChatConnection* chatConnection;

public:

    Client();
    ~Client();
  
    void Connect( std::string userName, byte usernameColor );
    void Disconnect();
  
    // if not connected throw SendMessageException?
    void PassMessage(Message* message);
  
    bool IsUnreadMessage();
    void GetLatestMessage(Message* message);

    bool IsNewActiveUserList();


    // TODO:
    void GetLatestActiveUserList();

};

// _CLIENT_H
#endif 
