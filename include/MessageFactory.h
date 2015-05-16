// MessageFactory.h

#ifndef _MESSAGE_FACTORY_H
#define _MESSAGE_FACTORY_H

#include "UserMessage.h"

// MessageFactory
class MessageFactory
{
private:

public:

	MessageFactory();
	~MessageFactory(); 

	
	UserMessage GetMessage( std::string messageString ); 
};


#endif
