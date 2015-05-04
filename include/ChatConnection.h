// ChatConnection.h

#include "MessageFactory.h"

// ChatConnection
class ChatConnection
{
private: 

	std::queue<Client> newClient; 
	
	std::vector<ClientAddress> clientAddresses; 
	
	UDPConnection* udpConnection; 

public:

	ChatConnection(); 
	~ChatConnection(); 
	
	// return true if there are new connected clients
	bool NewClientConnected();
	
	// if there's anything on the newUsers queue, return it.
	User GetLatestUserConnection(); 

	Message GetLatestMessage(); 
	
	// send a message to a particular clientId
	void SendMessage( int clientID, Message message ); 
	
	// send a message to all clients
	void SendMessageToAllClients( Message message ); 
};
