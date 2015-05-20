// ServerChatConnection.h
//
// ServerChatConnection manages connection level messages from/to clients
// while exposing application level messages to the Server class
//
// all the messages we recieve are from clients


#ifndef _SERVER_CHAT_CONNECTION_H
#define _SERVER_CHAT_CONNECTION_H

#include "ConnectionLayer/UDPServer.h"
#include "ConnectionLayer/IChatConnection.h"
#include "BeeChatException.h"


#include "User.h"
#include <map>

// ServerChatConnection
class ServerChatConnection : public IChatConnection
{

private:

    // message queue
    std::queue<struct Message> messageQueue; 
  
    // at the lower level we're sending messages to clients through UDP
    std::map<ClientID, struct sockaddr_in> clientAddressMap;

    class UDPServer* udpServer;
    
    void LogoffAddress( struct sockaddr_in address ); 
    ClientID LogonAddress( struct sockaddr_in address ); 
    bool IsAddressLoggedOn( struct sockaddr_in address ); 

public: 

    ServerChatConnection();
    ~ServerChatConnection();

    void Connect();
    void Disconnect();  

    void Run();

    bool IsUnreadMessages();
    void GetLatestMessage(struct Message* message);

    void SendMessageToClient( struct Message* message, ClientID clientID ); 
}; 

#endif
