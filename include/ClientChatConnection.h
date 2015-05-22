// ClientChatConnection.h
//
// ClientChatConnection manages/responds to connection level messages from the server.
// Application level messages are exposed to the Client owner class
// 
// All the messages we recieve are from the server

#ifndef _CLIENT_CHATCONNECTION_H
#define _CLIENT_CHATCONNECTION_H

#include "IChatConnection.h"
#include "ClientMessage.h"
#include "UDPClient.h"
#include <queue>

// ClientChatConnection
class ClientChatConnection : public IChatConnection
{
private:

	std::queue<struct Message> messageQueue; 
	class UDPClient* udpClient; 

public:
    
	ClientChatConnection(); 
	~ClientChatConnection(); 

	void Connect();
	void Disconnect(); 

	bool IsUnreadMessages(); 
	void GetLatestMessage( struct Message* message ); 

	void SendMessageToServer( struct Message* message ); 
}; 


#endif
