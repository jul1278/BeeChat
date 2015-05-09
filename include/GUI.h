/* GUI.h
 * ENB241 Project
 *
 * GUI class header
 *
 */

#ifndef _GUI_H
#define _GUI_H
#include <string>
#include <vector>
#include <queue>

#include <ncurses.h>
using std::string;
using std::vector;
using std::queue;


//stores string "TIME : USER : MESSAGE"
//command requests string (from user input que)
//command gives string (Store and print)

// FEATURES:
// windows
// text wrapping
// running chat screen
//
// userlist
// commands (pm's)
// servers?
// 

class GUI
{
public:
	GUI();
	~GUI();
	void initScreen();
	void initWindows();
	void Routine();

	string mRequested();
	void mRecieved(string message);

	void updateUsers(vector<string> users);

	int checkVulgar(string *message);
	string upperCase(string message);

	
// private:
	void printAscii(WINDOW *scr, char *gaphics[], int sizey, int sizex, int starty, int startx);
	void printServers(WINDOW *scr, int a);
	void printMessage(string message, int message_lines, int *h_index, int *attempt, int *message_len, int prev_len, int endline);
	void printUsers(WINDOW *scr);
	void printChat();
	
	void userInput();
	int selectServer();
	void showScreen(int a, int b);
	bool command(string message, int out_in);

	void addBan(string user_str);
	void remBan(string user_str);

	void test();

private:
	User _user;

	vector<string> DATA;
	vector<string> USERS;
	queue<string> MESSAGE_QUEUE;

	WINDOW *info_scr;
	WINDOW *servers_scr;
	WINDOW *chat_win;
	WINDOW *message_win;
	WINDOW *servers_win;
};



#endif
