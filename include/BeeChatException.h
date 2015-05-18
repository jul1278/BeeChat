// BeeChatException.h


#ifndef _BEECHAT_EXCEPTION_H
#define _BEECHAT_EXCEPTION_H

#include <exception>

//use enum for exception types? 
//need static counts for relevant exceptions - static meaning variable persists through destructors
//create text file error log to catch unhandled errors?
enum ExceptionType
{
    // connection issues
      //socket not free
        //
      //port connection refused
        //
      //port connection termination unsuccessful
        //
      //attempt to start a second server, cannot run a second server
        //notify user, deny connection, continue on  
      //server failed to start
        //try again, 3 iterations then terminate connection?  
      //client failed to start
        //try again, 3 iterations then terminate connection?
      //message for new user failed to send
        //try again? 3 iterations, then terminate user connection?
    
    //GUI issues
      //invalid message type
        //notify user and discard message
      //GUI interface failed to initialize
        //try again x3, notify user, then terminate program
          //why would this happen?
      //user list update failed
        //try again x3, re-request user list from server, try again x3, terminate program with countdown message
      //unrecognized command
        //notify user, discard message, continue
      //unrecognized input type of any kind
        //notify user, discard message, continue
    
    //command issues
      //server has disconnected unexpectedly
        //notify user, terminate with countdown message
      //client object has disappeared
        //terminate
          //why would this happen? could it?
      //message failed to send
        //try again x3 with counter, notify user on 3rd fail of failure and contnue
          //is this because server is busy? could wait and handle differently if so
      //message received is of unhandled type
        //notify sender (or server?), log error + message, then discard message and continue
      //command in received message is unknown
        //notify sender (or server?), log error + message, then discard message and continue
      
    //server issues
      //client ping not successful, user has disconnected unexpectedly
        //terminate user from list and connection, send message to all users that clients has disconnected
      //  
        
    //unknown issues
      //unknown exception (hopefully never throw this)
        //log error location (if possible) with server and terminate everything
          //try notifying user first?
      //  
    
};

// BeeChatException
class BeeChatException // : public std::exception
{
private:
  std::string message; 
  std::string Message() { return message; } 

public:
    
  BeeChatException();
  ~BeeChatException(); 

    //ExceptionType exceptionType( std::string exMessage ) {;}

};



// void ExceptionLog()
// {
//   //log exceptions to a text file on server's PC, or to a file on the server?
// }

#endif
