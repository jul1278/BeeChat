// IChatConnection.h
#ifndef _CHAT_CONNECTION_H
#define _CHAT_CONNECTION_H

#include "MessageFactory.h"
#include "User.h"
#include "UserMessage.h"
#include "ClientMessage.h"
#include "UDPClient.h"
#include "UDPServer.h"

// ChatConnection
class IChatConnection
{
public:

	ChatConnection(); 
	~ChatConnection(); 

	virtual void Connect() =0;
	virtual void Disconnect() =0; 
		
	virtual bool IsUnreadMessages() =0; 
	virtual void GetLatestMessage( Message** message ) =0; 
	
	virtual void SendMessage( Message* message ) =0; 
};

// _CHAT_CONNECTION_H
#endif
