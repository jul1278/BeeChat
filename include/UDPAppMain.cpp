// UDPApp

#include "UDP.h"
#include <pwd.h>
#include <iostream>

//========================================================
// Name: main
// Desc:
//========================================================
int main( int argc, char** arg )
{
	UDPConnection connection; 

	for ( int i = 0; i < argc; i++ ) {
		std::cout << arg[i] << std::endl; 
	}

	struct passwd *pws;
	pws = getpwuid(geteuid());

	std::string userName(pws->pw_name); 

	std::cout << pws->pw_name << std::endl; 
	std::cout << pws->pw_uid << std::endl; 
	std::cout << pws->pw_gid << std::endl; 
	std::cout << pws->pw_dir << std::endl;
	std::cout << pws->pw_shell << std::endl; 


	if ( std::string(arg[1]) == "server" ) {
		connection.StartServer(); 
	} else {

		std::string message( arg[2] ); 

		message = userName + " " + message; 

		connection.StartClient( message ); 
	}

	return 0; 

}