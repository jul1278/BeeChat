/* Windows.h
 * ENB241 Project
 *
 * Windows class header
 *
 */

#ifndef _WINDOWS_H
#define _WINDOWS_H

#include <ncurses.h>
#include <string>
#include <vector>
#include <queue>
using std::string;
using std::vector;
using std::queue;

const double CHAT_SIZE = 0.8;

class Windows
{
public:
	Windows(WINDOW **info, WINDOW **chat, WINDOW **message, WINDOW **users);
	Windows();
	~Windows();

	void setup();
	void initScreen();
	void initWindows();
	void resize();

private:
	WINDOW **info_scr;
	WINDOW **chat_win;
	WINDOW **users_win;
	WINDOW **message_win;
};



#endif
