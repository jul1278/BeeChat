// UDPClient.cpp
#include "UDPClient.h"

UDPConnection* clientListener;

// wrapper function which is friends with UDPConnection
// we can't pass a pointer to a member function to a thread
void* ClientListenerWrapper(void* threadId)
{
    clientListener->ListenerThread(threadId);
    return NULL;
}
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
    
    clientListener = this;
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
// Name: Start
// Desc:
//----------------------------------------------------------------------------------
void UDPClient::Start()
{
    // check if a thread has already started
    
    int res = pthread_create( &listenerThread, NULL, ClientListenerWrapper, NULL );
    
    if ( res ) {
        // error
        std::cout << "pthread_error()" << std::endl;
    }
}
//----------------------------------------------------------------------------------
// Name: SendToServer
// Desc:
//----------------------------------------------------------------------------------
void UDPClient::SendToServer( char* message )
{
    // package message up and send
    ClientMessage clientMessage;
    
    // HACK: build the server address
    struct sockaddr_in serverAddr;
    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    
    if (inet_aton("127.0.0.1", &serverAddr.sin_addr) == 0) {
        std::cout << "inet_aton() error" << std::endl;
    }
    
    memcpy( (void*)clientMessage.message, (void*)message, MESSAGE_LENGTH );
    
    // using serverAddress which we set up in the constructor
    memcpy( (void*)&clientMessage.address, (void*)&serverAddr, sizeof(serverAddr) );
    
    SendMessage( &clientMessage );
}
