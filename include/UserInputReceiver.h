// UserInputReceiver.h
#ifndef _USER_INPUT_RECEIVER_H
#define _USER_INPUT_RECEIVER_H

#include <queue>

//UserInputReceiver
class UserInputReceiver
{
private:

	std::queue<std::string> chatStringQueue; 

public:

	UserInputReceiver(); 
	~UserInputReciever(); 

	void Update();
	
	std::string GetLatestChatString(); 
};


#endif
