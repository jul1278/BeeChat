// ServerChatConnection.h
//
// ServerChatConnection manages connection level messages from/to clients
// while exposing application level messages to the Server class
//
// all the messages we recieve are from clients


#ifndef _SERVER_CHAT_CONNECTION_H
#define _SERVER_CHAT_CONNECTION_H

#include "IChatConnection.h"
#include "BeeChatException.h"
#include "UDPServer.h"
#include "Message.h"
#include "User.h"

// probably need other stuff
typedef unsigned int ClientID; 

// ServerChatConnection
class ServerChatConnection : public IChatConnection
{

private:

    // stores the name of the new users
    std::queue<User> newUserQueue;

    // message queue
    std::queue<Message> messageQueue; 
  
    // at the lower level we're sending messages to clients through UDP
    std::map<ClientID, struct sockaddr_in> clientAddressMap;

    UDPServer* udpServer;
    
    LogoffAddress( struct sockaddr_in address ); 
    LogonAddress( struct sockaddr_in address ); 

public: 

    ServerChatConnection();
    ~ServerChatConnection();

    void Connect();
    void Disconnect();  

    void Run();

    bool IsUnreadMessages();
    void GetLatestMessage(Message* message);

    void SendMessageToClient( Message* message, ClientID clientID ); 
 
    bool IsNewUser();
    void GetLatestUser(User* user);
}; 

#endif
