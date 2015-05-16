// // ChatConnection.cpp

// #include "ChatConnection.h"

// //-------------------------------------------------------------------
// // Name: ChatConnection
// // Desc: 
// //-------------------------------------------------------------------
// ChatConnection::ChatConnection()
// {

// }
// //-------------------------------------------------------------------
// // Name: ~ChatConnection
// // Desc: 
// //-------------------------------------------------------------------
// ChatConnection::~ChatConnection()
// {
// 	delete udpConnection; 
// }
// //-------------------------------------------------------------------
// // Name: GetLatestRawMessage
// // Desc: 
// //-------------------------------------------------------------------
// void ChatConnection::GetLatestRawMessage( ClientMessage* message )
// {
// 	if ( this->IsUnreadMessages() == true ) {

// 	}
// }
// //-------------------------------------------------------------------
// // Name: ChatConnection
// // Desc: 
// //-------------------------------------------------------------------
// void ChatConnection::SetUDPConnection( UDPConnection* setUDPConnection )
// {
// 	this->udpConnection = setUDPConnection; 
// }
// //-------------------------------------------------------------------
// // Name: ChatConnection
// // Desc: 
// //-------------------------------------------------------------------
// bool ChatConnection::IsUnreadMessages()
// {

// 	//TODO: not all messages will be exposed to the caller so either we deal with 'internal only'
// 	//      messages before this gets called or only return true if there are 'external' messages

// 	if ( this->messageQueue.empty() == false ) {
// 		return true; 
// 	}
// }
// //-------------------------------------------------------------------
// // Name: GetUnreadMessage
// // Desc: 
// //-------------------------------------------------------------------
// void ChatConnection::GetLatestMessage( UserMessage** message )
// {
// 	if ( this->IsUnreadMessages() ) {
		
// 		*message = new UserMessage();  

// 		User sender; 
// 		sender.clientID = 0; 
		

// 		(*message)->



// 	}	
// }
// //-------------------------------------------------------------------
// // Name: SendMessage
// // Desc: 
// //-------------------------------------------------------------------
// void ChatConnection::SendMessage(UserMessage* message)
// {
// 	// translate UserMessage to ClientMessage
// 	// send
// }

