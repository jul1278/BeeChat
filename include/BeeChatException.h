// BeeChatException.h


#ifndef _BEECHAT_EXCEPTION_H
#define _BEECHAT_EXCEPTION_H

// BeeChatException
class BeeChatException
{
private:
  std::string message
public:
  
  BeeChatException();
  ~BeeChatException(); 
  
  std::string Message() { return message; } 
  
};

#endif
