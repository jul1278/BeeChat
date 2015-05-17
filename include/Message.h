// Message.h

#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "User.h"

typedef unsigned char MESSAGE_TYPE; 
typedef unsigned char byte; 

// TODO: move these #define's somewhere more appropriate
//       also look at using an enum
#define MAX_NUM_USERNAME_CHAR 10
#define MAX_MESSAGE_LENGTH 128 


#define	LOGON_NOTIFY 0x01
// LOGON_NOTIFY - data is a string with the requested username
//                could in future hold a 'super user' password
//                format etc

#define	LOGOFF_NOTIFY 0x02
// LOGOFF_NOTIFY - no data required

#define	SERVER_QUERY 0x03 // eg when was user x last active 
#define	CLIENT_QUERY 0x04
// SERVER_QUERY 
// CLIENT_QUERY - not implemented yet

#define	KICK_NOTIFY 0x05
#define	BAN_NOTFIY 0x06
// KICK_NOTIFY
// BAN_NOTIFY - not implemented yet
//


// messages
#define	CHAT_MESSAGE 0x07
// CHAT_MESSAGE - data is (senders) USERNAME | USERNAME COLOR | TEXT COLOR | MESSAGE 
//                     MAX_NUM_USERNAME_CHAR | 1 BYTE         | 1 BYTE     | REMAINING  
#define	PRIVATE_MESSAGE 0x08

// format/colors etc
#define	USERNAME_FORMAT_NOTIFY 0x09
#define	ACTIVE_USER_LIST_NOTIFY 0x0a

// Ping
#define	PING_REQUEST 0x0b
#define	PING_RESPONSE 0x0c

// Message
struct Message
{
	MESSAGE_TYPE messageType; 
	char* messageData; 
}; 

// LogonMessage
struct LogonMessage
{
	char username[MAX_NUM_USERNAME_CHAR];
	ClientID clientID; // <- server use only 
	byte usernameColor; 
	byte textColor; 
};

struct LogoffMessage
{
	ClientID clientID; 
}; 

// ChatMessage
struct ChatMessage
{
	char username[MAX_NUM_USERNAME_CHAR]; 
	byte usernameColor;
	byte textColor; 
	char messageText[MAX_MESSAGE_LENGTH]; 

};

// _MESSAGE_H
#endif