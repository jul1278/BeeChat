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
  
    //Hi
    
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
    client = new Client(); 
    
    if ( client->Status() ) {
      // display a welcome screen commands whatever
    }
    
    if ( !server->IsRunning() ) {
      // we're not a server, display a message "You tried to be a server but a server already exists!" 
      ui->PostMessage( "You tried to be the server but a server is already running :(" ); 
    }
    

    
    messageFactory = new MessageFactory(); 
    
    

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
    
    if ( client->IsUnreadMessages()  ) {
      Message newMessage = client->GetLatestMessage();   
      
      //TODO: how do we decide what to do with the message?
      
      // if ( newMessage is a chat message )
      ui->PostNewMessage( newMessage ); 
      
      // else
      // TODO: another class should exist to sort out 'non-chat messages'
      //       BeeChatApp should only be responsible for delegating and coordinating the other modules
      //       manage program state
      this->HandleMessage( newMessage ); 
      
    }
    
    // check if there's a new active user list to display
    if ( client->NewActiveUserList() ) {
      
      // get the user list
      ui->ActiveUserList( activeUsers ); 
    }
    
    
    // TODO: set quit to 1 if we're quitting  
    
    
  }
  //---------------------------------------------------------------------
  // Name: ~BeeChatApp
  // Desc:
  //---------------------------------------------------------------------
  void HandleMessage( Message message )
  {
    // handle handle handle handle handle handle handle
    // handle handle handle handle handle handle handle
    // handle handle handle handle handle handle handle
    // handle handle handle handle handle handle handle
    // handle handle handle handle handle handle handle
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
