// AppMain.cpp

#include "BeeChatApp.h"
#include "UDPConnection.h"
#include "UDPServer.h"
#include "UDPClient.h"
#include <string>

int main( int argc, char** argv )
{ 
	// check arguments does the user want to be a server? otherwise we're a server
	// get requested username from arguments

    //UDPServer* server = new UDPServer();
    //UDPClient* client = new UDPClient();
    
    //server->Start();
    //client->Start();
    

    //while ( 1 ) {
    //   client->SendToServer("lol");
   // }
    
	// try to be a server if the user wants  
	BeeChatApp* beeChatApp = new BeeChatApp( "toby", 0x01, true );
    //BeeChatApp* clientTest = new BeeChatApp( "test", 0x01, false );
    
    
    while ( beeChatApp->Run() ) {
        //clientTest->Run();
    }

	return 0;
}
