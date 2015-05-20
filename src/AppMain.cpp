// AppMain.cpp

#include "BeeChatApp.h"
#include "ConnectionLayer/UDPConnection.h"
#include "ConnectionLayer/UDPServer.h"
#include "ConnectionLayer/UDPClient.h"
#include <string>

int main( int argc, char** argv )
{     
    std::string username;

    if ( argc > 1 ) {

        username = std::string(argv[1]); 

    } else {
        username = "user"; 
    }


	// try to be a server if the user wants  
	class BeeChatApp* beeChatApp = new BeeChatApp( username.c_str(), 0x01, true );
    //BeeChatApp* clientTest = new BeeChatApp( "test", 0x01, false );
    
    
    while ( beeChatApp->Run() ) {
        //clientTest->Run();
    }

	return 0;
}
