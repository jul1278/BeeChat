// ChatConnection.h
#ifndef _CHAT_CONNECTION_H
#define _CHAT_CONNECTION_H

#include "MessageFactory.h"

#include "UDPClient.h"
#include "UDPServer.h"


// ChatConnection
class ChatConnection
{
private: 

	std::queue<int> newClientId; 
	
	// maps clientID (integer) to a socket address
	// we only ever expose the ID to the above classes - not the client address
	std::map<int, ClientUDPAdress> clientAddressMap; 
		
	UDPConnection* udpConnection; 

public:

	ChatConnection(); 
	~ChatConnection(); 
	
	// return true if there are new connected clients
	bool IsNewClientConnection();
	
	// if there's anything on the newUsers queue, return it.
	int GetLatestClientID(); 
	
	bool IsUnreadMessage(); 
	Message GetLatestMessage(); 
	
	// send a message to a particular clientId
	void SendMessage( int clientID, Message message ); 
	
	// send a message to all clients
	void SendMessageToAllClients( Message message ); 
};

// _CHAT_CONNECTION_H
#endif
