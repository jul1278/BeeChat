//
//  BeeChatApp.cpp
//  BeeChat
//
//  Created by Julian  on 16/05/2015.
//  Copyright (c) 2015 Julian . All rights reserved.
//

#include "BeeChatApp.h"
#include "MessageFactory.h"
#include "server.h"

//---------------------------------------------------------------------
// Name: BeeChatApp
// Desc:
//---------------------------------------------------------------------
BeeChatApp::BeeChatApp( std::string username, bool userWantsToBeServer )
{
    //ui = new LachlansUIThing();
    
    // try to start server
    // does the server need to know our username?
    server = new Server();
    client = new Client();
    
    client->Connect( username );
    
    //ui->PresentInfoScreen();
    
    messageFactory = new MessageFactory();
    
}
//---------------------------------------------------------------------
// Name: ~BeeChatApp
// Desc:
//---------------------------------------------------------------------
BeeChatApp::~BeeChatApp()
{
    delete client;
    delete server;
    delete ui;
    delete messageFactory;
}
//---------------------------------------------------------------------
// Name: Run
// Desc:
//---------------------------------------------------------------------
int BeeChatApp::Run()
{
    
    int quit = 0;
    
    // TODO: ask the UI if the user wants to quit

    
    // TODO: has the user typed anything in?

    
    // client is only going to tell us about chat messages,
    // it will handle other messages internally
    if ( client->IsUnreadMessages()  ) {
        
        UserMessage message
        
        client->GetLatestMessage( &message );
        
        //TODO: how do we decide what to do with the message?
        
        // TODO: post message to the screen if we got one
        
    }
    
    // TODO: check the client if there's a new active user list to display

    server->Run();
    
    // TODO: set quit to 1 if we're quitting
}
//---------------------------------------------------------------------
// Name: ~BeeChatApp
// Desc:
//---------------------------------------------------------------------
void BeeChatApp::HandleMessage( Message message )
{
    // handle handle handle handle handle handle handle
    // handle handle handle handle handle handle handle
    // handle handle handle handle handle handle handle
    // handle handle handle handle handle handle handle
    // handle handle handle handle handle handle handle
}
