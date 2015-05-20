// UDPClient.h
#ifndef _UDP_CLIENT_H
#define _UDP_CLIENT_H

#include "ConnectionLayer/UDPConnection.h"

// UDPClient
class UDPClient : public UDPConnection 
{
public:

    UDPClient();
    ~UDPClient();
    
    void Start(); 
    
    void SendToServer( char* message );
};

// _UDP_CLIENT_H
#endif




