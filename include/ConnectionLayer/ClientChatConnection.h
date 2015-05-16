// ClientChatConnection.h
//
// ClientChatConnection manages/responds to connection level messages from the server.
// Application level messages are exposed to the Client owner class
// 
// All the messages we recieve are from the server

#ifndef _CLIENT_CHATCONNECTION_H
#define _CLIENT_CHATCONNECTION_H

#include "IChatConnection.h"
#include "UserMessage.h"
#include "ClientMessage.h"
#include <queue>

// ClientChatConnection
class ClientChatConnection : public IChatConnection
{
private:

	std::queue<ClientMessage> clientMessageQueue; 
	UDPClient* udpClient; 

public:
    
	ClientChatConnection(); 
	~ClientChatConnection(); 

	void Connect( std::string username );
	void Disconnect(); 

	bool IsUnreadMessages(); 
	void GetLatestMessage( UserMessage** message ); 

	void SendMessage( UserMessage* message ); 
}; 


#endif
