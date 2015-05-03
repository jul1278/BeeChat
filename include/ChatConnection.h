// ChatConnection.h

#include "MessageFactory.h"

// ChatConnection
class ChatConnection
{
private: 

public:

	ChatConnection(); 
	~ChatConnection(); 

	// what should this return; 
	void GetLatestClientConnection(); 

	Message GetLatestMessage(); 
	void SendMessage( int userID ); 
};
