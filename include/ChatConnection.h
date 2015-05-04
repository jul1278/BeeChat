// ChatConnection.h

#include "MessageFactory.h"

// ChatConnection
class ChatConnection
{
private: 

	std::queue<User> newUsers; 
	
	UDPConnection* udpConnection; 

public:

	ChatConnection(); 
	~ChatConnection(); 
	
	// if there's anything on the newUsers queue, return it.
	User GetNewUserConnection(); 


	Message GetLatestMessage(); 
	void SendMessage( int userID ); 
};
