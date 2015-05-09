// UDPApp

#include "UDPServer.h"
#include "UDPClient.h"
#include <pwd.h>
#include <iostream>

//========================================================
// Name: main
// Desc:
//========================================================
int main( int argc, char** arg )
{

	UDPServer server; 
	UDPClient client; 

	server.StartServer();
	client.StartClient(); 


	return 0; 
}