// MessageFactory.h

#ifndef _MESSAGE_FACTORY_H
#define _MESSAGE_FACTORY_H

// Message
struct Message
{


};

// MessageFactory
class MessageFactory
{
private:

public:

	MessageFactory();
	~MessageFactory(); 

	
	Message GetMessage( std::string messageString ); 
};


#endif
