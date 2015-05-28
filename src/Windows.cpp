/* Windows.h
 * ENB241 Project
 *
 * Windows class header
 *
 */

#include "Windows.h"

Windows::Windows(WINDOW **info, WINDOW **chat, WINDOW **message, WINDOW **users) {
	info_scr = info;
	chat_win = chat;	// need to pass pointer to pointer
	users_win = users;
	message_win = message;
	setup();
}

Windows::Windows() {

}

Windows::~Windows() {

}


void Windows::setup() {
	initScreen();
	initWindows();
}

void Windows::initScreen() {
	initscr();
	// cbreak();
	raw();
	noecho();
	curs_set(0);
	start_color();
	init_pair(1, COLOR_RED, 	COLOR_BLACK);
	init_pair(2, COLOR_GREEN, 	COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, 	COLOR_BLACK);
	init_pair(4, COLOR_BLUE, 	COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, 	COLOR_BLACK);
	init_pair(7, COLOR_WHITE, 	COLOR_BLACK);
	//STORE USERNAME + user list (request)
}

void Windows::initWindows() {
	int row, col;
	getmaxyx(stdscr,row,col);
	*info_scr 	= newwin(row, col, 0, 0);
	*chat_win 	= newwin((int)(row*CHAT_SIZE), 	 		(int)(col*CHAT_SIZE)-1, 	0, 						0);
	*message_win = newwin((int)(row*(1-CHAT_SIZE))+1, 	col, 						(int)(row*CHAT_SIZE), 	0);
	*users_win = newwin((int)(row*CHAT_SIZE), 			(int)(col*(1-CHAT_SIZE))+1,	0, 						(int)(col*CHAT_SIZE));
    wborder(*info_scr, 		'|', '|', '-','-','+','+','+','+');
    wborder(*chat_win, 		'|', '|', '-','-','+','+','+','+');
    wborder(*message_win, 	'|', '|', '-','-','+','+','+','+');
    wborder(*users_win, 	'|', '|', '-','-','+','+','+','+');
    keypad(*message_win, TRUE);
}

void Windows::resize() {
	int row, col;
	getmaxyx(stdscr,row,col);
	*info_scr 	= newwin(row, col, 0, 0);
	*chat_win 	= newwin((int)(row*CHAT_SIZE), 	 		(int)(col*CHAT_SIZE)-1, 	0, 						0);
	*message_win = newwin((int)(row*(1-CHAT_SIZE))+1, 	col, 						(int)(row*CHAT_SIZE), 	0);
	*users_win = newwin((int)(row*CHAT_SIZE), 			(int)(col*(1-CHAT_SIZE))+1,	0, 						(int)(col*CHAT_SIZE));
    keypad(*message_win, TRUE);
	wclear(*message_win);									
	wclear(*users_win);									
	wclear(*chat_win);										
	wclear(stdscr);										
    wborder(*info_scr, 		'|', '|', '-','-','+','+','+','+');
    wborder(*chat_win, 		'|', '|', '-','-','+','+','+','+');
    wborder(*message_win, 	'|', '|', '-','-','+','+','+','+');
    wborder(*users_win, 	'|', '|', '-','-','+','+','+','+');
	wrefresh(stdscr);										
	wrefresh(*chat_win);										
	wrefresh(*message_win);									
	wrefresh(*users_win);									


	// showScreen(CHAT, 0);
}

