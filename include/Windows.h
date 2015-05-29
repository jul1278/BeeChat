/* Windows.h
 * ENB241 Project
 *
 * Windows class header
 *
 */

#ifndef _WINDOWS_H
#define _WINDOWS_H

#include <iostream>					///< required for: cout
#include <ncurses.h>				///< required for: ncurses
#include <string>					///< required for: strings
#include <vector>					///< required for: vectors
#include <queue>					///< required for: queues
using std::string;
using std::vector;
using std::queue;
using std::cout;

const double CHAT_SIZE = 0.8;		///< ratio of chat screen to user and message screens

class Windows
{
public:
	Windows(WINDOW **info, WINDOW **chat, WINDOW **message, WINDOW **users);	///< initializes member variables
	Windows();						///< constructs a temporary Windows object
	~Windows();						///< deconstructs a Windows object

	void setup();					///< setup initalizes all ncurses
	void initScreen();				///< initializes ncurses settings
	void initWindows();				///< initializes display screens
	void resize();					///< resizes the chat screen
	bool checkMin();

private:
	WINDOW **info_scr;				///< the splash screen
	WINDOW **chat_win;				///< the chat window
	WINDOW **users_win;				///< the userlist window
	WINDOW **message_win;			///< the message box
};

// TODO:
// default resize args


#endif
