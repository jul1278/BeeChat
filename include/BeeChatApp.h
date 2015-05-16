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
  Client* client;
  
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

    client->Connect( username ); 
    
    ui->PresentInfoScreen(); 

    messageFactory = new MessageFactory(); 
    
  }
  //---------------------------------------------------------------------
  // Name: Run
  // Desc:
  //---------------------------------------------------------------------
  int Run()
  {
    
    int quit = 0; 
    
    // if the user wants to quit
    if ( ui->UserIsQuitting() ) {
      // tell the server that we are quitting
      client->Disconnect(); 
      
      server->Disconnect();
      
      return 0; 
    }
    
    // has the usertyped anything in? 
    if ( ui->NewMessages() ) {
      
      // 1. get the string from the UI
      std::string newMessage = ui->GetLatestMessage(); 
      
      // turn the string into a message object
      // some messages could be normal chat, some could be commands etc 
      UserMessage message = MessageFactory( newMessage ); 
      
      // send to the server
      client->SendMessage( message ); 
      
    }
    
    // client is only going to tell us about chat messages, 
    // it will handle other messages internally
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
    

    server->Run(); 

    
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
