#ifndef _USER_H
#define _USER_H

#include <string>

typedef unsigned char ClientID; 
typedef unsigned char byte; 

// User
struct User
{
  ClientID clientID;
  std::string username;   
  byte usernameColor;
  byte textColor;  

}; 

#endif
