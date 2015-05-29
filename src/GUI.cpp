/* GUI.h
 * ENB241 Project
 *
 * GUI class header
 *
 */

#include "GUI.h"

GUI::GUI(UserL *user, vector<UserL> *users, vector<string> *chatlog, WINDOW **info, WINDOW **chat, WINDOW **message, WINDOW **users_scr) {
	_user = user;
	_users = users;
	_chatlog = chatlog;
	info_scr = info;
	chat_win = chat;
	users_win = users_scr;
	message_win = message;
}

GUI::GUI() {

}

GUI::~GUI() {

}


// const char *INFO_ASCII[] = {" _____       __      ",
// 						  "|_   _|     / _|     ", 
// 						  "  | | _ __ | |_ ___  ", 
// 						  "  | || '_ \\|  _/ _ \\ ", 
// 						  " _| || | | | || (_) |", 
// 						  " \\___/_| |_|_| \\___/ "};   
						  
const char *BEE_ASCII[] = {"______           _____ _           _   ",
						  "| ___ \\         /  __ \\ |         | |  ",
						  "| |_/ / ___  ___| /  \\/ |__   __ _| |_ ",
						  "| ___ \\/ _ \\/ _ \\ |   | '_ \\ / _` | __|",
						  "| |_/ /  __/  __/ \\__/\\ | | | (_| | |_ ",
						  "\\____/ \\___|\\___|\\____/_| |_|\\__,_|\\__|"};

const char *YOU_HAVE[] = {"_____.___.                ___ ___                     ",
						  "\\__  |   | ____  __ __   /   |   \\_____ ___  __ ____  ",
						  " /   |   |/  _ \\|  |  \\ /    ~    \\__  \\\\  \\/ // __ \\ ",
						  " \\____   (  <_> )  |  / \\    Y    // __ \\\\   /\\  ___/ ",
						  " / ______|\\____/|____/   \\___|_  /(____  /\\_/  \\___  >",
						  " \\/                            \\/      \\/          \\/ "};

const char *BEEN_KICKED[] = {"__________                        ____  __.__        __              .___",
						 	 "\\______   \\ ____   ____   ____   |    |/ _|__| ____ |  | __ ____   __| _/",
						 	 " |    |  _// __ \\_/ __ \\ /    \\  |      < |  |/ ___\\|  |/ // __ \\ / __ | ",
						 	 " |    |   \\  ___/\\  ___/|   |  \\ |    |  \\|  \\  \\___|    <\\  ___// /_/ | ",
						 	 " |______  /\\___  >\\___  >___|  / |____|__ \\__|\\___  >__|_ \\\\___  >____ | ",
						 	 "        \\/     \\/     \\/     \\/          \\/       \\/     \\/    \\/     \\/ "};

void GUI::printAscii(WINDOW *scr, const char *graphics[], int sizey, int sizex, int starty, int startx) {
	int ii;
	for(ii = 0; ii < sizey; ii++) {
		mvwprintw(scr, starty+ii, startx, graphics[ii]);
	}
}

void GUI::printServers(WINDOW *scr, int a) {

}

void GUI::printUsers() {
	if(_user->isTimedout()) {
		return;
	}

	int ii;
	wclear(*users_win);
    wborder(*users_win, 	'|', '|', '-','-','+','+','+','+');
	mvwprintw(*users_win,1,1, "Main Server");

	for(ii = 0; ii < (*_users).size(); ii++) {
		if((*_users)[ii].getPriviledges() == ADMIN) {
			wattron(*users_win, COLOR_PAIR(5));
		}
		else if((*_users)[ii].getPriviledges() == SADMIN) {
			wattron(*users_win, COLOR_PAIR(6));
		}
		if((*_users)[ii].getUser() == (*_user).getUser()) {
			wattron(*users_win, A_REVERSE);
			// mvwprintw(*users_win,ii+2,USERS_OFFSET, (*_users)[ii].getUser().c_str());
			// wattroff(*users_win, A_REVERSE);
		}
		mvwprintw(*users_win,ii+2,USERS_OFFSET, (*_users)[ii].getUser().c_str());
		wattrset(*users_win, A_NORMAL);
	}
	wrefresh(*users_win);
}

void GUI::printTimeout() {
	mvwprintw(stdscr, 3,3, "YOU ARE IN TIMEOUT");
	// int row, col;
	// getmaxyx(*info_scr,row,col);
	// printAscii(*info_scr, BEE_ASCII, 6, 39, (int)(row*0.1), (col-39)/2);
	wrefresh(stdscr);
}

void GUI::printKick() {
	mvwprintw(stdscr, 3,3, "YOU HAVE BEEN KICKED.");
	int row, col;
	getmaxyx(stdscr,row,col);
	printAscii(stdscr, YOU_HAVE, 6, 54, (col-6)/2, (col-54)/2);
	printAscii(stdscr, BEEN_KICKED, 6, 73, (col-6)/2, (col-73)/2);
	refresh();
	endwin();
	sleep(3);
}

void GUI::showScreen(SCRN screen) {
	switch(screen) {
		case INFO:
			int row, col;
			getmaxyx(*info_scr,row,col);
			// printAscii(*info_scr, BEE_ASCII, 6, 21, (int)(row*0.1), (col-21)/2);
			printAscii(*info_scr, BEE_ASCII, 6, 39, (int)(row*0.1), (col-39)/2);
			mvwprintw(*info_scr, row-20,  4, "/b{TEXT}  --  bold font");
			mvwprintw(*info_scr, row-19,  4, "/u{TEXT}  --  underlined font");
			mvwprintw(*info_scr, row-18, 4, 	"/i{TEXT}  --  italic font (not currently implemented)");
			mvwprintw(*info_scr, row-17, 4, 	"/c{TEXT}  --  placeholder");
			mvwprintw(*info_scr, row-16, 4, 	"/colour{TEXT}  --  coloured font (red, green, blue, yellow, magenta, cyan, white)");

			mvwprintw(*info_scr, row-12, 4, 	"/help                           --  reopens this screen");
			mvwprintw(*info_scr, row-11, 4, 	"/kick    <user/all> <reason*>   --  kicks user");
			mvwprintw(*info_scr, row-10, 4, 	"/mute    <user/all> <reason*>   --  mutes user");
			mvwprintw(*info_scr, row-9, 4, 	"/unmute  <user/all>             --  unmutes user");
			mvwprintw(*info_scr, row-8, 4, 	"/poke    <user>                 --  pokes user");
			mvwprintw(*info_scr, row-7, 4, 	"/pm      <user> <message>       --  sends user a private message");
			mvwprintw(*info_scr, row-6, 4, 	"/exit                           --  exits the program");
			mvwprintw(*info_scr, row-5, 4, 	"/ignore  <user>                 --  you will not recieve messages from this user");
			mvwprintw(*info_scr, row-4, 4, 	"/timeout <user> <reason*>       --  sends user to his own room");
			mvwprintw(*info_scr, row-3, 4, 	"/release <user>                 --  brings user back to main chat");

			wrefresh(*info_scr);
			break;

		case SERV:
			// printServers(servers_scr);
			break;

		case CHAT:
			wrefresh(stdscr);
			wclear(stdscr);
			printUsers();
			wclear(*message_win);
		    wborder(*message_win, 	'|', '|', '-','-','+','+','+','+');
			wrefresh(*message_win);
			printChat();
			break;
	}
}














































void GUI::printChat(int offset) {
	if(_user->isTimedout()) {
		return;
	}

	int row, col;
	getmaxyx(*chat_win, row, col);
	wclear(*chat_win);
    wborder(*chat_win, 	'|', '|', '-','-','+','+','+','+');
	// string fontcommands[] = {"/b{", "/i{", "/u{", "/c{", "/red{", "/green{", "/yellow{", "/blue{", "/magenta{", "/cyan{", "/white{"};

	string message;
	int message_len;

	while(_chatlog->size() > MAX_HISTORY) {
		_chatlog->erase(_chatlog->begin());
	}

	int ii;
    int m_index;
    int message_lines = 0;

	int lim = (*_chatlog).size()-row+2-offset;
	if (lim < 0) {lim = 0;}
 	for(m_index = lim; m_index < (*_chatlog).size()-offset; m_index++) {

 		message = (*_chatlog)[m_index];
		message_len = (*_chatlog)[m_index].size();

		for(ii = 0; ii < NFONTCOMMANDS; ii++) {
			int font_loc = 1;
			int font_size = fontcommands[ii].size();
			while((font_loc = message.find(fontcommands[ii])) != string::npos) {
				message = message.substr(font_loc+font_size);			// ERROR HERE!!!!!!!!!!!!!!
				message_len -= font_size+1;								//+1 for escape (cant do, what if /b{rgrsgdr)
			}
		}

		if(message_len>col-2) {
		message_lines++;
		message_len -= col-4;
		int temp = message_len/(col-4-NEWLINE_OFFSET);
		message_lines += temp + 1;
		}
		else {message_lines++;}
 	}


 	int h_index = 1;
	int attempt = 0;
	int jj, command_found;
 	for(m_index = lim; m_index < (*_chatlog).size()-offset; m_index++) {
		message = (*_chatlog)[m_index];
		message_len = (*_chatlog)[m_index].size();


		if(message.find("/") == string::npos) {														// if no /
			int prev_len = 0;
			printMessage(message, message_lines, &h_index, &attempt, &message_len, &prev_len, 1);			// print
		}
		else {																						// if /
			int font_loc, font_end;
			int message_len_sofar = 0;
			int prev_len = 0;
			vector<int> current_atr; //wanted stack, but cant check if already in stack (QUEUE = FILA)
			current_atr.reserve(10);

			while((message.find("/") != string::npos) || (message.find("}") != string::npos)) {
				command_found = 0;
				int slash_shorter = 0;
				int bracket_shorter = 0;
				// int loc_b = 
				// int loc_s = 
				if((message.find("/") != string::npos) && (message.find("}") != string::npos)) {
					if(message.find("/") < message.find("}")) {
						font_loc = message.find("/");
						slash_shorter = 1;
					}
					else {
						font_loc = message.find("}");
						bracket_shorter = 1;
					}
				}
				else if(message.find("/") != string::npos) {
					font_loc = message.find("/");
					slash_shorter = 1;
				}
				else if(message.find("}") != string::npos) {
					font_loc = message.find("}");
					bracket_shorter = 1;
				}


				if(slash_shorter) {										// look for command
					for(ii = 0; ii < NFONTCOMMANDS; ii++) {	
						int font_size = fontcommands[ii].size();

						if(message.substr(font_loc,font_size).find(fontcommands[ii]) != string::npos) {	// if command,
							//if command found
							command_found = 1;
							
							//print all before
							string message_seg = message.substr(0,font_loc);
							message_len_sofar += message_seg.size(); 
							printMessage(message_seg, message_lines, &h_index, &attempt, &message_len_sofar, &prev_len, 0);
							prev_len = message_len_sofar;

							//trunk message
							// message = message.erase(0,font_loc+font_size-1);
							message = message.substr(font_loc+font_size);
							//add atr (if not added)
							for(jj = 0; jj < current_atr.size(); jj++) {
								if(ii == current_atr[jj]) {
									jj = -1;
									break;
								}
							}
							if(jj != -1) {
								current_atr.push_back(ii);
								switch(ii) {
									case 0:
										wattron(*chat_win, A_BOLD);


										break;
									case 1:
										// wattron(*chat_win, A_ITALIC?);
										break;
									case 2:
										wattron(*chat_win, A_UNDERLINE);
										break;
									case 3:
										// wattron(*chat_win, A_COLOUR?);
										break;
									case 4:
										wattron(*chat_win, COLOR_PAIR(1));
										break;

									case 5:
										wattron(*chat_win, COLOR_PAIR(2));
										break;

									case 6:
										wattron(*chat_win, COLOR_PAIR(3));
										break;

									case 7:
										wattron(*chat_win, COLOR_PAIR(4));
										break;

									case 8:
										wattron(*chat_win, COLOR_PAIR(5));
										break;

									case 9:
										wattron(*chat_win, COLOR_PAIR(6));
										break;

									case 10:
										wattron(*chat_win, COLOR_PAIR(7));
										break;
								}
							}
							break;
						}
					}
					if(!command_found) {
						// command not found
						font_loc = message.find("/");
						//print slash

						string message_seg = message.substr(0,font_loc+1);
						message_len_sofar += message_seg.size(); 
						printMessage(message_seg, message_lines, &h_index, &attempt, &message_len_sofar, &prev_len, 0);
						prev_len = message_len_sofar;
						//trunk message
						// message = message.erase(0,font_loc+font_size-1);
						message = message.substr(font_loc+1);											//what if / at end?
					}
				}
				else if(bracket_shorter) {								// look for end
					//if end found

					if(!current_atr.empty()) {
						//print all before
						string message_seg = message.substr(0,font_loc);
						message_len_sofar += message_seg.size(); 
						printMessage(message_seg, message_lines, &h_index, &attempt, &message_len_sofar, &prev_len, 0);
						prev_len = message_len_sofar;

						//trunk message
						// message = message.erase(0,font_loc+font_size-1);
						message = message.substr(font_loc+1);						//+1 from delim -1 from font_loc balance

						switch(current_atr.back()) {
							case 0:
								wattroff(*chat_win, A_BOLD);
								break;
							case 1:
								// wattroff(*chat_win, A_ITALIC?);
								break;
							case 2:
								wattroff(*chat_win, A_UNDERLINE);
								break;
							case 3:
								// wattroff(*chat_win, A_COLOUR?);
								break;
							case 4:
								wattroff(*chat_win, COLOR_PAIR(1));
								break;

							case 5:
								wattroff(*chat_win, COLOR_PAIR(2));
								break;

							case 6:
								wattroff(*chat_win, COLOR_PAIR(3));
								break;

							case 7:
								wattroff(*chat_win, COLOR_PAIR(4));
								break;

							case 8:
								wattroff(*chat_win, COLOR_PAIR(5));
								break;

							case 9:
								wattroff(*chat_win, COLOR_PAIR(6));
								break;

							case 10:
								wattroff(*chat_win, COLOR_PAIR(7));
								break;
						}
						current_atr.pop_back();
					}
					else {
						//no current atr

						//print all before
						string message_seg = message.substr(0,font_loc+1);
						message_len_sofar += message_seg.size(); 
						printMessage(message_seg, message_lines, &h_index, &attempt, &message_len_sofar, &prev_len, 0);
						prev_len = message_len_sofar;

						//trunk message
						// message = message.erase(0,font_loc+font_size-1);
						message = message.substr(font_loc+1);						//+1 from delim -1 from font_loc balance
					}
				}
			}
			string message_seg = message;
			message_len_sofar += message_seg.size(); 
			if(message_seg != "") {
				printMessage(message_seg, message_lines, &h_index, &attempt, &message_len_sofar, &prev_len, 1);
			}
			else {
				h_index++;
			}
		}
		wattrset(*chat_win, A_NORMAL);	// REMOVE FROM VECTOR?
	}
	wrefresh(*chat_win);
}

void GUI::printMessage(string message, int message_lines, int *h_index, int *attempt, int *message_len, int *prev_len, int endline) {
	int row, col;
	getmaxyx(*chat_win, row, col);

	if((*message_len) > col-2) {
		if(message_lines-(*attempt)<=row-2) {													//
			mvwprintw(*chat_win,(*h_index),*prev_len+1,(message.substr(0,col-4-*prev_len)+"..").c_str());	//
			(*h_index)++;																		//
		}																						//		tryprint+trunkate
		message = message.substr(col-4-*prev_len);														//		  (*h_index),(*attempt),message, (*message_len)
		(*message_len) -= (col-4);																//			  must be pointers
		(*attempt)++;
		(*prev_len) = -1;																			//
		while((*message_len) > col-2-NEWLINE_OFFSET) {
			if(message_lines-(*attempt)<=row-2) {
				mvwprintw(*chat_win,(*h_index),NEWLINE_OFFSET,(message.substr(0, col-4-NEWLINE_OFFSET-*prev_len)+"..").c_str());
				(*h_index)++;
			}
			message = message.substr(col-4-NEWLINE_OFFSET-*prev_len);
			(*message_len) -= (col-4-NEWLINE_OFFSET);
			(*attempt)++;
		}
		if(message_lines-(*attempt)<=row-2) {
			mvwprintw(*chat_win,(*h_index),NEWLINE_OFFSET,message.c_str());
			// (*h_index)++;
			(*h_index) += endline;
		}
		(*message_len) += NEWLINE_OFFSET-1;													
		(*attempt)++;
	}
	else {
		if(message_lines-(*attempt)<=row-2) {
			mvwprintw(*chat_win,(*h_index),*prev_len+1,message.c_str());
			(*h_index) += endline;
		}
		(*attempt)+= endline;
	}
}

