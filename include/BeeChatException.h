// BeeChatException.h


#ifndef _BEECHAT_EXCEPTION_H
#define _BEECHAT_EXCEPTION_H

#include <exceptions>

// BeeChatException
class BeeChatException : public exception
{
private:
  std::string message
public:
  
  BeeChatException();
  BeeChatException( std::string exMessage ); 
  ~BeeChatException(); 
  
  std::string Message() { return message; } 
  
};

#endif
