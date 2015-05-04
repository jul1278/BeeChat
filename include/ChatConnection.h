// ChatConnection.h

#include "MessageFactory.h"

// ChatConnection
class ChatConnection
{
private: 

	std::queue<User> newUsers; 

public:

	ChatConnection(); 
	~ChatConnection(); 

	// what should this return; 
	void GetLatestClientConnection(); 
	
	User GetNewUser(); 

	Message GetLatestMessage(); 
	void SendMessage( int userID ); 
};
