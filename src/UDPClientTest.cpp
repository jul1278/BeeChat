// UDPClientTest.cpp

#include "UDPServer.h"
#include "UDPClient.h"
#include "ClientMessage.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

//-------------------------------------------------------------------
// Name:
// Desc: 
//-------------------------------------------------------------------
int main()
{
	srand(time(0));  

	UDPClient testClient; 

	testClient.Start(); 

	char* message = new char[MESSAGE_LENGTH]; 
	// message[0] = (97 + ( rand() % (122 - 97) )); 
	 

	// printf("Sent: %s\n", message );
	
	// testClient.SendToServer( message );

	while ( 1 ) {

		std::string input;
		getline( std::cin, input); 	

		memset( message, 0, MESSAGE_LENGTH ); 
		memcpy( message, input.c_str(), MESSAGE_LENGTH ); 

		//message = input.c_str(); 
		testClient.SendToServer( message );

		// wait until we got a message then print it out
		if ( testClient.IsUnreadMessages() ) {
			ClientMessage clientMessage; 

			testClient.LatestMessage( &clientMessage ); 

			std::string str = clientMessage.message; 

			printf( "Received: %s\n", str.c_str() ); 
		}
	}
}
