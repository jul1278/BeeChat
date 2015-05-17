// IChatConnection.h
#ifndef _CHAT_CONNECTION_H
#define _CHAT_CONNECTION_H

#include "MessageFactory.h"
#include "User.h"
#include "Message.h"
#include "ConnectionLayer/ClientMessage.h"
#include "ConnectionLayer/UDPClient.h"
#include "ConnectionLayer/UDPServer.h"

// ChatConnection
class IChatConnection
{
public:

	IChatConnection(); 
	~IChatConnection(); 

	virtual void Connect() =0;
	virtual void Disconnect() =0; 
		
	virtual bool IsUnreadMessages() =0; 
	virtual void GetLatestMessage( Message* message ) =0; 
};

// _CHAT_CONNECTION_H
#endif
