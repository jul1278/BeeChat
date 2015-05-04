#ifndef _BEECHAT_APP_H
#define _BEECHAT_APP_H

#include "Client.h"
#include "Server.h"
#include "MessageFactory.h"
#include "UI.h"

// BeeChatApp 
class BeeChatApp
{
private:
  
  LachlansUIThing* ui
  
  // server object
  Server* server; 

  // client object
  Client* client
  
  MessageFactory* messageFactory; 

public: 
  
  //---------------------------------------------------------------------
  // Name: BeeChatApp
  // Desc:
  //---------------------------------------------------------------------
  BeeChatApp( std::string username, bool userWantsToBeServer )
  {
    
    ui = new LachlansUIThing(); 
    
    // try to start server
    // does the server need to know our username?
    server = new Server(); 
    
    if ( server->IsRunning() ) {
      // we're not a server, display a message "You tried to be a server but a server already exists!" 
      ui->PostMessage( "You tried to be the server but a server is already running :(" ); 
    }
    
    messageFactory = new MessageFactory(); 
    
    client = new Client(); 

  }
  //---------------------------------------------------------------------
  // Name: Run
  // Desc:
  //---------------------------------------------------------------------
  int Run()
  {
    
    int quit = 0; 
    
    // check if server is running 
    if ( server->IsRunning() ) {
      
    }
    
    // check if the ui has messages
    if ( ui->NewMessages() ) {
      
      // get string from ui
      std::string newMessage = ui->GetLatestMessage(); 
      
      // turn the string into a message struct
      Message message = MessageFactory( newMessage ); 
      
      client->SendMessage( message ); 
      
    }
    
    // TODO: set quit to 1 if we're quitting  
    
    
  }
  //---------------------------------------------------------------------
  // Name: ~BeeChatApp
  // Desc:
  //---------------------------------------------------------------------
  ~BeeChatApp()
  {
    delete client; 
    delete server; 
    delete ui; 
    delete messageFactory; 
    
  }

};

// _BEECHAT_APP_H
#endif
