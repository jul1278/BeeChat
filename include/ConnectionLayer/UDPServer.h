// UDPConnection.h

#ifndef _UDP_SERVER_H
#define _UDP_SERVER_H

#include "ConnectionLayer/UDPConnection.h"

// UDPServer
class UDPServer : public UDPConnection 
{
public:

	UDPServer(); 
	~UDPServer();
    
    void Start();

}; 

// _UDP_CONNECTION_H
#endif

