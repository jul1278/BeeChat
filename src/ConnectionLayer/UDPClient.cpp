// UDPClient.cpp
#include "UDPClient.h"

//----------------------------------------------------------------------------------
// Name: UDPClient
// Desc:
//----------------------------------------------------------------------------------
UDPClient::UDPClient()
{
    hostent* pHost;
    pHost = (hostent*) gethostbyname( (char*) "localhost" );
    
    serverAddress.sin_addr.s_addr = *((in_addr_t*)pHost->h_addr);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    
    // we always need to get a socket
    //printf("Started client.\n");
    // get a socket
    udpSocket = socket( AF_INET, SOCK_DGRAM, 0 );
    
    if ( udpSocket == -1 ) {
        std::cout << "socket() error" << std::endl;
    }
    
    
}
//----------------------------------------------------------------------------------
// Name: ~UDPClient
// Desc:
//----------------------------------------------------------------------------------
UDPClient::~UDPClient()
{
    close( udpSocket );     
}
//----------------------------------------------------------------------------------
// Name: SendToServer
// Desc:
//----------------------------------------------------------------------------------
void UDPClient::SendToServer( char* message )
{
    // package message up and send
    ClientMessage clientMessage;
    
    memcpy( clientMessage.message, message, MESSAGE_LENGTH );
    
    clientMessage.address = serverAddress;
    SendMessage( &clientMessage ); 
}