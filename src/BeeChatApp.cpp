//
//  BeeChatApp.cpp
//  BeeChat
//
//  Created by Julian  on 16/05/2015.
//  Copyright (c) 2015 Julian . All rights reserved.
//

#include "BeeChatApp.h"
#include "MessageFactory.h"
#include "Server.h"

//---------------------------------------------------------------------
// Name: BeeChatApp
// Desc:
//---------------------------------------------------------------------
BeeChatApp::BeeChatApp( std::string username, byte usernameColor, bool userWantsToBeServer )
{
    quit = 0;
    this->username = username;
    

    // try to start server
    // does the server need to know our username?
    server = new Server();
    client = new Client();
    
    server->Connect();
    client->Connect( this->username, usernameColor );
    
    //ui = new LachlansUIThing();
    UserL temp(username,ADMIN);
    messageFactory = new MessageFactory(temp);
    if(messageFactory->quit) {quit = 1;}
    //ui->PresentInfoScreen();
    
    
}
//---------------------------------------------------------------------
// Name: ~BeeChatApp
// Desc:
//---------------------------------------------------------------------
BeeChatApp::~BeeChatApp()
{
    delete client;
    delete server;
    
    //delete ui;
    delete messageFactory;
}
//---------------------------------------------------------------------
// Name: Run
// Desc:
//---------------------------------------------------------------------
int BeeChatApp::Run()
{
    // TODO: ask the UI if the user wants to quit
    // TODO: has the user typed anything in?

    messageFactory->userInput();
    
    client->Connect( this->username, 0x01 );

    // TRY TO SEND MESSAGE
    if(messageFactory->checkMessage()) {
        std::string message_str = messageFactory->getMessage();

        struct Message message;
        message.messageType = CHAT_MESSAGE;
        struct ChatMessage* chatMessage = (ChatMessage*) message.messageData; 
        strcpy(chatMessage->messageText, message_str.c_str());
        client->PassMessage(&message);
    }
    
    // TRY TO RECIEVE MESSAGE    
    if ( client->IsUnreadMessage() ) {
        struct Message message; 
        client->GetLatestMessage( &message );
        
        if ( message.messageType == CHAT_MESSAGE ) {
            struct ChatMessage* chatMessage = (struct ChatMessage*) message.messageData;
            std::string chatMessageString(chatMessage->messageText);
            messageFactory->storeMessage(chatMessageString);
        } 
        // else {
        //
        // }
    }
    
    // TRY TO RUN SERVER
    server->Run();
    

    // Continue until message queue is cleared
    if(!messageFactory->checkMessage()) {
        return !(messageFactory->quit);
    }
    else {
        return 1;
    }
}

