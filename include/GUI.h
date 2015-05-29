/* GUI.h
 * ENB241 Project
 *
 * GUI class header
 *
 */

#ifndef _GUI_H
#define _GUI_H

#include <ncurses.h>							///< required for: graphics
#include <string>								///< required for: strings
#include <vector>								///< required for: vectors
#include <queue>								///< required for: queues
#include "UserL.h"								///< required for: user and userlist
using std::string;
using std::vector;
using std::queue;

enum SCRN {INFO, SERV, CHAT};					///< used to select a screen to print (showscreen())
const int USERS_OFFSET	 = 3;					///< the x axis offset of users on the user window
const int NEWLINE_OFFSET = 26;					///< the x axis offset of wrapped messages
const int MAX_HISTORY	 = 40;					///< the maximum chatlog length

const string fontcommands[] = {"/b{", "/i{", "/u{", "/c{", "/red{", "/green{", "/yellow{", "/blue{", "/magenta{", "/cyan{", "/white{"};
const int NFONTCOMMANDS	 = sizeof(fontcommands)/sizeof(*fontcommands);
// const int NFONTCOMMANDS	 = 11;

class GUI
{
public:
	GUI(UserL *user, vector<UserL> *users, 		///< constructs and initalizes member variables in the GUI object
		vector<string> *chatlog, WINDOW **info, 
		WINDOW **chat, WINDOW **message, 
		WINDOW **users_scr);
	GUI();										///< constructs a temporary GUI object
	~GUI();										///< deconstructs a GUI object

	void printServers(WINDOW *scr, int a);		///<
	void printUsers();							///< prints all users, and their privilidges in the user window
	void printTimeout();						///< temporary block screen if the user is timed out
	void printKick();							///< final display screen before user is kicked
	void showScreen(SCRN screen);				///< method used to help increase readability of code
	void printChat(int offset = 0);				///< prints the chatlog to the screen, with wrapping and fonts


	void printMessage(string message, 			///< prints an individual message for the printChat function
		int message_lines, int *h_index, 		///< keeps track of height, position, wrapping and avaliable room
		int *attempt, int *message_len, 
		int *prev_len, int endline);

	void printAscii(WINDOW *scr, 				///< prints ascii text (or image) to the given location and window
		const char *graphics[], int sizey, 
		int sizex, int starty, int startx);

private:
	UserL *_user;								///< pointer to the main User object, so it remains up to date
	vector<UserL> 	*_users;					///< pointer to the main userlist, so it remains up to date
	vector<string> 	*_chatlog;					///< pointer to the main chatlog, so it remains up to date

	WINDOW **info_scr;							///< pointer to the info screen window
	WINDOW **chat_win;							///< pointer to the chat screen window
	WINDOW **users_win;							///< pointer to the user screen window
	WINDOW **message_win;						///< pointer to the message box window
};



#endif
