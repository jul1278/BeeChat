// UDPServer.h
#define _UDP_SERVER_H
#ifndef _UDP_SERVER_H

const int PORT = 6969;
const int MESSAGE_LENGTH = 512; 

// UDPServer
class UDPServer
{
private:

	struct sockaddr_in serverAddress;

	bool stopListening; 

	socklen_t sockLen; 
	
	pthread_mutex_t messageQueueMutex; 
	pthread_mutex_t listenerMutex; 

	int serverSocket;

	std::queue<ClientMessage> clientMessageQueue; 

public:

	UDPServer();
	~UDPServer(); 

	void StartServer(); 
	void StopServer(); 

	void SendToClient( ClientMessage* clientMessage ); 

	bool IsNewMessage(); 
	void GetLatestMessage( ClientMessage* receivedClientMessage ); 
};

// _UDP_SERVER_H
#endif