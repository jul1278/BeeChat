/* GUI.h
 * ENB241 Project
 *
 * GUI class header
 *
 */

#ifndef _GUI_H
#define _GUI_H

#include "UserL.h"

#include <ncurses.h>
#include <string>
#include <vector>
#include <queue>
using std::string;
using std::vector;
using std::queue;

#define INFO 0
#define SERV 1
#define CHAT 2
#define USERS_OFFSET 3
#define NEWLINE_OFFSET 26
#define NFONTCOMMANDS 11

class GUI
{
public:
	GUI(UserL *user, vector<UserL> *users, vector<string> *chatlog, WINDOW **info, WINDOW **chat, WINDOW **message, WINDOW **users_scr);
	GUI();
	~GUI();

	void printAscii(WINDOW *scr, const char *graphics[], int sizey, int sizex, int starty, int startx);
	void printServers(WINDOW *scr, int a);
	void printUsers();
	void printTimeout();
	void showScreen(int a);

	void printChat(int offset = 0);
	void printMessage(string message, int message_lines, int *h_index, int *attempt, int *message_len, int *prev_len, int endline);

private:
	UserL *_user;
	vector<UserL> 	*_users;
	vector<string> 	*_chatlog;
	// queue<string> 	*_messageQueue;

	WINDOW **info_scr;
	WINDOW **chat_win;
	WINDOW **users_win;
	WINDOW **message_win;
};



#endif
