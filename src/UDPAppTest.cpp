// UDPApp
#include <pwd.h>
#include <iostream>

#include "UDPServer.h"
#include "UDPClient.h"

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