// ClientChatConnection.h
//
// ClientChatConnection manages/responds to connection level messages from the server.
// Application level messages are exposed to the Client owner class
// 
// All the messages we recieve are from the server

#ifndef _CLIENT_CHATCONNECTION_H
#define _CLIENT_CHATCONNECTION_H

#include "ConnectionLayer/IChatConnection.h"
#include "Message.h"
#include "ConnectionLayer/ClientMessage.h"
#include <queue>

// ClientChatConnection
class ClientChatConnection : public IChatConnection
{
private:

	std::queue<Message> messageQueue; 
	UDPClient* udpClient; 

public:
    
	ClientChatConnection(); 
	~ClientChatConnection(); 

	void Connect();
	void Disconnect(); 

	bool IsUnreadMessages(); 
	void GetLatestMessage( Message* message ); 

	void SendMessageToServer( Message* message ); 
}; 


#endif
