/* MessageFactory.h
 * ENB241 Project
 *
 * MessageFactory class header
 *
 */

#ifndef _FACTORY_H
#define _FACTORY_H

#include "GUI.h"				///< required for: print functions
#include "Windows.h"			///< required for: ncurses functions
// #include "UserL.h"			///< included in: GUI.h
//#include "Snake.h"			///< included in: source file
#include <sstream>				///< required for: streams
#include <iostream>				///< required for: cout (ding)
// #include <stdlib.h>			///< required for: 




enum MESS_DIR {OUT, IN, COM};
enum COMMAND {HELP, KICK, MUTE, UNMUTE, POKE, PM, EXIT, IGNORE, TIMEOUT, RELEASE, SNAKE, TEST, PING, PINGB, NONE = -1};
const string commands[] = {"/help", "/kick", "/mute", "/unmute", "/poke", "/pm", "/exit", "/ignore", "/timeout", "/release", "/snake", "/test", "/pingRequest", "/pingBack"};
const int NCOMMANDS = sizeof(commands)/sizeof(*commands);






class MessageFactory
{
public:
	MessageFactory(UserL user);							///< constructs the message factory object and initialises member variables.
	MessageFactory();									///< constructs a temporary object
	~MessageFactory();									///< deconstructs a message factory object
			
	/** \brief called to try and collect user input.
      * This method must be looped, and collects input
      * a key at a time- userInput also sorts backspacing
      * resizing, chat scrolling, checking printable chars
      * priviledges, swearing and formatting.
      */	
	void userInput();									///< non blocking user input, must loop through- final message stored in message queue.
	void updateUsers();									///< sends a ping request to all other users, which send back there details
	void removeUser(string user);						///< removes given specified user object from userlist.
	void addUser(string username, int priviledges);		///< removes given specified user object from userlist.
				
	string getMessage();								///< withdraws the first message placed in the message queue, if none, returns ""
	bool checkMessage();								///< returns true if message in queue, else returns false
	void storeMessage(string message);					///< stores a message in queue, and refreshes the chat screen
	bool checkVulgar(string *message);					///< replaces 'badwords' with 'goodwords', returns true if a badword is found
	string upperCase(string message);					///< returns an output equal to the upper case input

	/** \brief Called for both inputs and outputs.
      * \param message message to be checked for commands
      * \param out_in signifys whether the message is ingoing or outgoing
      * \return flag true if command found, false if not
      * 
      * This method searches all in-going and out-going
      * commands and handles them appropriatly.
      * The return flag can be used to limit displaying
      * raw commands to the chat.
      */
	bool command(string message, MESS_DIR out_in);

	/// Warning ensures commands have the correct args.
	bool Warning(string command, string arg_str, 
				 UserL arg_obj, bool user_exists, 
				 bool admin_only, bool rank_matters);
				
	void dummyText();									///< example messages and users
	void testText();									///< quick test of multiple GUI features
	bool quit;											///< quit flag, set to quit the program

private:
	GUI _Gooey;											///< GUI object, to handle graphics
	Windows _Win;										///< Windows object, to handle ncurses setup

	UserL _user;										///< local user object
	vector<UserL> 	_users;								///< user list
	vector<string> 	_chatlog;							///< message history
	queue<string> 	_messageQueue;						///< message queue from which the server reads

	WINDOW *info_scr;									///< the splash screen
	WINDOW *chat_win;									///< the chat window
	WINDOW *users_win;									///< the userlist window
	WINDOW *message_win;								///< the message box
};



#endif
