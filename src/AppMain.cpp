// AppMain.cpp

#include "BeeChatApp.h"
#include <string>

int main( int argc, char** argv )
{ 
  // check arguments does the user want to be a server? otherwise we're a server
  // get requested username from arguments
  
  // try to be a server if the user wants  
  BeeChatApp* beeChatApp = new BeeChatApp( "Default User", 0x01, true ); 

  while ( beeChatApp->Run() ); 
  
  return 0;
}
