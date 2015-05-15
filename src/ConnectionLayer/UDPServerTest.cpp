// UDPServerTest.cpp
#include "ClientMessage.h"
#include "UDPConnection.h"
#include "UDPServer.h"
#include "UDPClient.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

std::vector<ClientMessage> clients; 

//-------------------------------------------------------------------
// Name:
// Desc: 
//-------------------------------------------------------------------
int main()
{
	srand(time(0));  

	UDPServer testServer; 

	testServer.Start(); 

	while ( 1 ) {

		// wait until we got a message then print it out
		if ( testServer.IsUnreadMessages() ) {

			ClientMessage clientMessage; 

			testServer.LatestMessage( &clientMessage ); 

			std::string str = clientMessage.message;

			// add the address where the message came from if we haven't got it already
			if ( std::find( clients.begin(), clients.end(), clientMessage ) == clients.end() ) {
				clients.push_back( clientMessage );		
			}

			printf( "%i: ", clientMessage.address);
			printf(" %s\n", str.c_str() ); 		

			for ( int i = 0; i < clients.size(); i++ ) {

				clientMessage.address = clients[i].address; 
				testServer.SendMessage( &clientMessage );
			}
		}			
	}
}
