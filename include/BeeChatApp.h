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
    Client* client;
  
    MessageFactory* messageFactory;
    void HandleMessage( Message message );
public: 

    
    BeeChatApp( std::string username, bool userWantsToBeServer );
    ~BeeChatApp();
    
    int Run();

};

// _BEECHAT_APP_H
#endif
