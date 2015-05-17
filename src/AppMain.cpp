// AppMain.cpp

#include "BeeChatApp.h"

int main( int argc, char** argv )
{
  
  // check arguments does the user want to be a server? otherwise we're a server
  // get requested username from arguments
  
  // try to be a server if the user wants  
  BeeChatApp* beeChatApp = new BeeChatApp( string username, userWantsToBeAServer ); 

  while ( beeChatApp->Run() ); 
  
  return 0;
}
