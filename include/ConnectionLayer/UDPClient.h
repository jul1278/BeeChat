// UDPClient.h
#ifndef _UDP_CLIENT_H
#define _UDP_CLIENT_H

#include "UDPConnection.h"
#include "ClientMessage.h"

// UDPClient
class UDPClient : public UDPConnection
{
public:

    UDPClient();
    ~UDPClient();
    void SendToServer( char* message );
};

// _UDP_CLIENT_H
#endif
