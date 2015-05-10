// UDPApp
#include <pwd.h>
#include <iostream>

#include "UDPServer.h"
#include "UDPClient.h"

//----------------------------------------------------------
// Name: main
// Desc:
//----------------------------------------------------------
int main( int argc, char** arg )
{
	UDPServer server; 
	UDPClient clientA;
    UDPClient clientB;

	server.StartServer();
    
	clientB.StartClient();
	clientA.StartClient();
     

	char* messageA = new char[MESSAGE_LENGTH];
    char* messageB = new char[MESSAGE_LENGTH];

	messageA[0] = 'a';
    messageA[1] = 'y';
    messageA[2] = 'y';
    messageA[3] = 'A';
    
    messageB[0] = 'a';
    messageB[1] = 'y';
    messageB[2] = 'y';
    messageB[3] = 'B';
    
    clientB.SendToServer( messageB );
	clientA.SendToServer( messageA );
	

	ClientMessage clientMessage;

	// we never stop ever
	while( 1 ) {

		// 
		while ( server.IsUnreadMessages() ) {

			server.GetLatestMessage( &clientMessage );

			std::string str; 
			str = clientMessage.message;

			std::cout << "Server received: " << str << std::endl; 
            
			server.SendToClient( &clientMessage );
		}

        //
        while ( clientB.IsUnreadMessages() ) {
            
            memset( &clientMessage, 0, sizeof(ClientMessage) );
            
            clientB.GetLatestMessage( &clientMessage );
            
            std::string str;
            str = clientMessage.message;
            
            std::cout << "Client B received: " << str << std::endl;
            
            clientB.SendToServer( clientMessage.message );
            
        }
        //
        while ( clientA.IsUnreadMessages() ) {
            
            memset( &clientMessage, 0, sizeof(ClientMessage) );
            
            clientA.GetLatestMessage( &clientMessage );
            
            std::string str;
            str = clientMessage.message;
            
            std::cout << "Client A received: " << str << std::endl;
            
            clientA.SendToServer( clientMessage.message );
            
        }
	}

	return 0; 
}