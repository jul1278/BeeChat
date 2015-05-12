// ServerChatConnection.h

class ServerChatConnection : public ChatConnection
{

private:
  
  std::vector<User> user; 
  
  // 
  UDPServer* udpServer; 
  
public: 
  
  ServerChatConnection();
  ~ServerChatConnection(); 
  
  // 
  void Run()
  {
    // check our UDP connection to see if we've got any new messages
    
    // check if the sender address of the message is one we already know about
    // or if it's a new client that wants to join the server
  }

  
}; 
