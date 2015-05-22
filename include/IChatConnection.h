// IChatConnection.h
#ifndef _CHAT_CONNECTION_H
#define _CHAT_CONNECTION_H

#include "Message.h"

// ChatConnection
class IChatConnection
{
public:

	IChatConnection() {}
	~IChatConnection() {}

	virtual void Connect() =0;
	virtual void Disconnect() =0; 
		
	virtual bool IsUnreadMessages() =0; 
	virtual void GetLatestMessage( struct Message* message ) =0; 
};

// _CHAT_CONNECTION_H
#endif
