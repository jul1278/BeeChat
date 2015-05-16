// UserMessage.h
//
// Julian Pattie
//
// UserMessage is a DTO for interfacing between Client and ClientChatConnection
//
//
//
#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "User.h"
#include <cstring>

typedef unsigned char byte;


// ideas...
enum MESSAGE_TYPE
{
	LOGON_NOTIFY,
	LOGOFF_NOTIFY,

	SERVER_QUERY, // eg when was user x last active 
	CLIENT_QUERY,

	KICK_NOTIFY,
	BAN_NOTFIY,

	// messages
	CHAT_MESSAGE,
	PRIVATE_MESSAGE,

	// format/colors etc
	USERNAME_FORMAT_NOTIFY,

	ACTIVE_USER_LIST_NOTIFY,

	// Ping
	PING_REQUEST,
	PING_RESPONSE
};

// UserMessage
struct UserMessage
{
	//------------------------------------------------------------------
	// Name: UserMessage
	// Desc: makes a deep copy of the messageData
	//       is responsible for its memory
	//------------------------------------------------------------------
	UserMessage( User sender, User dest, byte* messageData, unsigned int dataLength )
	{
		this->sender = sender; 
		this->dest = dest; 

		this->messageData = new byte[dataLength];
		memcpy( (void*)&this->messageData, (void*)messageData, dataLength );  
	}
    //------------------------------------------------------------------
    // Name: UserMessage
    // Desc:
    //------------------------------------------------------------------
    UserMessage( byte* messageData, unsigned int dataLength )
    {
        this->messageData = new byte[dataLength];
        memcpy( (void*)&this->messageData, (void*)messageData, dataLength );
    }
    //------------------------------------------------------------------
    // Name: UserMessage
    // Desc:
    //------------------------------------------------------------------
	UserMessage(){}
	//------------------------------------------------------------------
	// Name: UserMessage
	// Desc:
	//------------------------------------------------------------------
	~UserMessage()
	{
		delete messageData; 
	}

	User sender; 
	User dest; 

	// TODO: 
	// 
	// MESSAGE_TYPE LogonNotification, LogoffNotification, Kick/Ban/etc Notification
	//              ChatMessage, PrivateMessage, UsernameFormatNotification, ActiveUserListNotification
	//              PingRequest, PingResponse 
	//
	// MessageFormat (ChatMessage only!) color/font specifier 
	//
	// Time timeSent (important? probably not)

	unsigned int dataLength; 
	byte* messageData; 

};


#endif