// UDPServerTest.cpp
#include "UDPConnection.h"
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

	UDPServer testServer; 

	testServer.Start(); 

	while ( 1 ) {

		// wait until we got a message then print it out
		if ( testServer.IsUnreadMessages() ) {

			ClientMessage clientMessage; 

			testServer.LatestMessage( &clientMessage ); 

			std::string str = clientMessage.message; 

			printf( "%i: ", clientMessage.address);
			printf(" %s\n", str.c_str() ); 
		}

	}

}
