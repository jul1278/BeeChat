/* MessageFactory.h
 * ENB241 Project
 *
 * MessageFactory class header
 *
 */

#ifndef _FACTORY_H
#define _FACTORY_H

#include "GUI.h"
// #include "UserL.h"
#include "Windows.h"
//#include "Snake.h"
#include <sstream>
#include <iostream>
#include <stdlib.h>

#define OUT 0
#define IN 	1
#define COM 3

enum COMMAND {HELP, KICK, MUTE, UNMUTE, POKE, PM, EXIT, IGNORE, TIMEOUT, RELEASE, SNAKE, TEST, NONE = -1};
const string commands[] = {"/help", "/kick", "/mute", "/unmute", "/poke", "/pm", "/exit", "/ignore", "/timeout", "/release", "/snake", "/test"};
const int NCOMMANDS = sizeof(commands)/sizeof(*commands);
// const int NCOMMANDS = 12;

class MessageFactory
{
public:
	MessageFactory(UserL user);
	MessageFactory(); // call setup()
	~MessageFactory();

	void userInput(); //bool?
	void updateUsers();
	void removeUser(string user);

	string getMessage();
	bool checkMessage();
	void storeMessage(string message);
	bool checkVulgar(string *message);
	string upperCase(string message);
	bool command(string message, int out_in);
	bool Warning(string command, string arg_str, UserL arg_obj, bool user_exists, bool admin_only, bool rank_matters);

	void dummyText();
	void testText();
	bool quit;

private:
	GUI _Gooey;
	Windows _Win;

	UserL _user;
	vector<UserL> 	_users;
	vector<string> 	_chatlog;
	queue<string> 	_messageQueue;

	WINDOW *info_scr;
	WINDOW *chat_win;
	WINDOW *users_win;
	WINDOW *message_win;
};



#endif




// Windows, resize, doesnt change GUI windows
// command, doesnt pickup /



