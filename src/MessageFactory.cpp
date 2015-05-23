/* MessageFactory.h
 * ENB241 Project
 *
 * MessageFactory class header
 *
 */

#include "MessageFactory.h"
using namespace std;

MessageFactory::MessageFactory(UserL user) {
	_chatlog.reserve(100);
	_users.reserve(15);
	dummyText();

	_user = user;
	_Win = Windows(&info_scr, &chat_win, &message_win, &users_win);
	_Gooey = GUI(&_user, &_users, &_chatlog, &info_scr, &chat_win, &message_win, &users_win);
} 

MessageFactory::MessageFactory() {

} 

MessageFactory::~MessageFactory() {

}

void MessageFactory::dummyText() {
	_chatlog.push_back("[05:30:12] : Feyre    : Hey everyone!");    
	_chatlog.push_back("[06:25:15] : Mike     : Oh hey :)");    
	_chatlog.push_back("[05:30:52] : Tim      : Poop");    
	_chatlog.push_back("[05:30:19] : Feyre    : Uhh, what?");    

	_users.push_back(UserL("Feyre", SADMIN));
	_users.push_back(UserL("Tim", REGULAR));
	_users.push_back(UserL("Mike", REGULAR));
	_users.push_back(UserL("Liam", SADMIN));
	_users.push_back(UserL("Johnny", REGULAR));
}


void MessageFactory::updateUsers() {

}


void MessageFactory::removeUser(string user) {
	int ii;
	for(ii = 0; ii < _users.size(); ii++) {							
		if(user == _users[ii].getUser()) {
			_users.erase(_users.begin()+ii);
			break;
		}	
	}	
	if(user == "all") {
		for(ii = 0; ii < _users.size(); ii++) {							
			if(_users[ii].getPriviledges() < ADMIN) {
				_users.erase(_users.begin()+ii);
				ii--;
			}
		}	
	}
	_Gooey.printUsers();	
}


string MessageFactory::getMessage() {
	string message = _messageQueue.front();
	_messageQueue.pop();
	return message;
}

bool MessageFactory::checkMessage() {
	if(!_messageQueue.empty()) {return 1;}
	else {return 0;}
}

void MessageFactory::storeMessage(string message) {
	if(!command(message, IN)) {
		_chatlog.push_back(message);
		if(_user.getPriviledges() != TIMEDOUT) {
			_Gooey.printChat();
		}
	}
}

bool MessageFactory::checkVulgar(string *message) {
	int ii, jj = 0;
	string badwords[] =  {"cunt",		"fucker", "fuck", "dick"    , "slut"  , "shit", "ass", "cock"  , "pussy" , "fag"   , "bitch"         , "wanker"   , "whore"};
	string goodwords[] = {"croissant", 	"Tucker", "duck", "wee-wee" , "muppet", "poop", "bum", "donger", "kitten", "wizard", "b with an itch", "gentleman", "loon"};
	int size = 13;
	int loc;

	for(ii = 0; ii < size; ii++) {
		if((loc = upperCase(*message).find(upperCase(badwords[ii]))) != string::npos) {
			(*message).replace(loc,badwords[ii].size(),goodwords[ii]);
			jj = 1; // change to ++ if you want n. of badwords
		}
	}
	if(jj) {_user.incSwears();}
	return jj;
}

string MessageFactory::upperCase(string message) {
	for (string::iterator it = message.begin(); it != message.end(); ++ it)
    *it = toupper(*it);
  return message;
}
























string message_str_g ="";
// int offset = 0; // link with gUI

void MessageFactory::userInput() {
	if(_user.getPriviledges() == TIMEDOUT) {return;}

	int offset = 0;

	int row, col;
	getmaxyx(message_win, row, col);
	wmove(message_win, row/2, (int)(col*0.1));
	wprintw(message_win,message_str_g.c_str());

	char time_char[11];

	string temp = "";
	curs_set(1);
	nodelay(message_win,1);
	int c = wgetch(message_win);

	if(c != '\n') {
		if(c == KEY_RESIZE) {
			c = wgetch(message_win);
			_Win.resize();
			getmaxyx(message_win, row, col);
			_Gooey.showScreen(CHAT);
			if(message_str_g.size() >= (int)(col*0.8)) {
				message_str_g = message_str_g.substr(0,(int)(col*0.8));
			}
			wclear(message_win);
		    wborder(message_win, 	'|', '|', '-','-','+','+','+','+');
			wmove(message_win, row/2, (int)(col*0.1));
			wprintw(message_win,message_str_g.c_str());
			wrefresh(message_win);
			return;
		}
		else if(c == KEY_BACKSPACE) {
			message_str_g = message_str_g.substr(0,message_str_g.size()-1);
			wclear(message_win);
		    wborder(message_win, 	'|', '|', '-','-','+','+','+','+');
			wmove(message_win, row/2, (int)(col*0.1));
			wprintw(message_win,message_str_g.c_str());
			wrefresh(message_win);
			// sleep(2);
		}
		else if(c == KEY_UP) {
			getmaxyx(chat_win, row, col);
			int lim = _chatlog.size()-row+2;
			if(lim < 0) {lim = 0;}
			if(offset < lim) {
				offset++;
				_Gooey.printChat();
			}
		}
		else if(c == KEY_DOWN) {
			if(offset > 0) {
				offset--;
				_Gooey.printChat();
			}
		}
		else if(c == ERR) {return;}
		else if(message_str_g.size() >= (int)(col*0.8)) {return;} 
		else if(!isprint(c)) {
			storeMessage("             <SERVER> : You have entered a non printable character.");
			wmove(message_win, row/2, (int)(col*0.1)+message_str_g.length());
		}
		else {
			message_str_g += c;
			waddch(message_win,c);
			wrefresh(message_win);
		} 
		return;
	}

	
	if(_user.getPriviledges() == 0) {
		wclear(message_win);	//MAYBE: write own clear function that wont clear border.
	    wborder(message_win, 	'|', '|', '-','-','+','+','+','+');
		wrefresh(message_win);
		return;
	}

	int swore = checkVulgar(&message_str_g);
	if(swore) {
		if(_user.getSwears() >= 5) {
			//kick user (remove from other clients)
			endwin();
			exit(EXIT_SUCCESS);
		}
		else if(_user.getSwears() >= 4) {
			storeMessage("             <SERVER> : This is your final warning, swear again and you will be kicked.");
		}
		else if(_user.getSwears() >= 3) {
			storeMessage("             <SERVER> : Please refrain from profanity.");
		}
	}


	// pad username
	string user_str = _user.getUser();
	user_str.append(8 - user_str.length(), ' ');

	// time
	time_t timer;
	time(&timer);
	struct tm * timeinfo;
	timeinfo = localtime(&timer);
	strftime(time_char,11,"[%H:%M:%S]",timeinfo);
	string time_str(time_char);

	string DATA_str = time_str + " : " + user_str + " : " + message_str_g;

	wclear(message_win);	//MAYBE: write own clear function that wont clear border.
    wborder(message_win, 	'|', '|', '-','-','+','+','+','+');
	wrefresh(message_win);

	//if not null
	if(!command(DATA_str, OUT)) {
		_messageQueue.push(DATA_str);
	}
	message_str_g = "";
} 























bool MessageFactory::command(string message, int out_in) {
	// message = message.substr(24); 		//bad to edit? maybe only give it the message part
	Snake snakeGame;


	// INITIALIZE VARIABLES
	int ii, jj = 0;
	string this_user = _user.getUser();
	string commands[] = {"/help", "/kick", "/mute", "/unmute", "/poke", "/pm", "/exit", "/ignore", "/timeout", "/release", "/snake"};
	string fontcommands[] = {"/b{", "/i{", "/u{", "/c{", "/red{", "/green{", "/yellow{", "/blue{", "/magenta{", "/cyan{", "/white{"};
	string command_str;
	string user_str;
	string arg_str;
	string arg_str2;
	string temp;

	// EXTRACT TOKENS
	stringstream ss(message);
    ss >> temp;					//time
    ss >> temp;					// :
    ss >> user_str;				//user
    ss >> temp;					// :
    ss >> command_str;			//command
    ss >> arg_str;				//arg 			WHAT IF NO ARG?

	if(!ss.eof()) {
		arg_str2 = "";
		while(!ss.eof()) {
			ss >> temp;
			arg_str2 += temp + " ";
		}
	}

    // INITIAL CHECK FOR COMMAND
	if(command_str.substr(0,1) != "/") {return 0;}			//UPDATE LATER (incase text style changes (time:name:message));

	// CHECK FOR FONT COMMANDS
	for(ii = 0; ii < NFONTCOMMANDS; ii++) {
		if(command_str.substr(0,fontcommands[ii].size()) == fontcommands[ii]) {
			return 0;
		}
	}

	// CHECK FOR COMMANDS
	for(ii = 0; ii < NCOMMANDS; ii++) {
		if(command_str == commands[ii]) {
			jj = ii+1;
			break;
		}
	}

	// CHECK USER IS ONLINE -- move to command specific if commands have arg1 as not user
	UserL arg_obj;
    int user_exists = 0;
	for(ii = 0; ii < _users.size(); ii++) {
		if(arg_str == _users[ii].getUser()) {
			user_exists = 1;
			arg_obj = _users[ii];
		}
	}


	// USER SENT COMMAND
	if(out_in == OUT) {		
		switch(jj) {

			case HELP:
				//disp help screen
				return 1;



			case KICK:
				if(arg_str == "all") {
					_messageQueue.push(message);
					// _messageQueue.push("             <SERVER> : " + this_user + " has kicked " + arg_str + ".");
				}
				else if(!user_exists) {
					if (arg_str=="")		{storeMessage("             <SERVER> : Please enter the target user.");}
					else if (arg_str!="")	{storeMessage("             <SERVER> : " + arg_str + " is not online.");}
					return 1;
				}
				else if(_user.getPriviledges() < ADMIN) {
					storeMessage("             <SERVER> : Insufficient priviledges. (ADMIN only)");
					return 1;
				}
				else if (arg_str == this_user) {
					storeMessage("             <SERVER> : You have tried to, uhh.. kick yourself?");
					return 1;
				}
				else if(_user.getPriviledges() <= arg_obj.getPriviledges()) {
					storeMessage("             <SERVER> : You cannot kick a superior or matching rank.");
					return 1;
				}
				else if(user_exists) {
					_messageQueue.push(message);
					// _messageQueue.push("             <SERVER> : " + this_user + " has kicked " + arg_str + ".");
				}
				return 1;



				// you cant kick all


			case MUTE:
				//check_msg.Command(MUTE, user_exists, thi)
				if(arg_str == "all") {
					_messageQueue.push(message);
				}
				else if(!user_exists) {
					if (arg_str=="")		{storeMessage("             <SERVER> : Please enter the target user.");}
					else if (arg_str!="")	{storeMessage("             <SERVER> : " + arg_str + " is not online.");}
					return 1;
				}
				else if(_user.getPriviledges() < ADMIN) {
					storeMessage("             <SERVER> : Insufficient priviledges. (ADMIN only)");
					return 1;
				}
				else if (arg_str == this_user) {
					storeMessage("             <SERVER> : You cannot mute yourself.");
					return 1;
				}	
				else if(_user.getPriviledges() <= arg_obj.getPriviledges()) {
					storeMessage("             <SERVER> : You cannot mute a superior or matching rank.");
					return 1;
				}
				else if(user_exists) {
					_messageQueue.push(message);
				}
				return 1;





			case UNMUTE:
				if(arg_str == "all") {
					_messageQueue.push(message);
				}
				else if(!user_exists) {
					if (arg_str=="")		{storeMessage("             <SERVER> : Please enter the target user.");}
					else if (arg_str!="")	{storeMessage("             <SERVER> : " + arg_str + " is not online.");}
					return 1;
				}
				else if(_user.getPriviledges() < ADMIN) {
					storeMessage("             <SERVER> : Insufficient priviledges. (ADMIN only)");
					return 1;
				}
				else if (arg_str == this_user) {
					storeMessage("             <SERVER> : You cannot unmute yourself.");
					return 1;
				}	
				// else if(_user.getPriviledges() <= arg_obj.getPriviledges()) {
				// 	storeMessage("             <SERVER> : You cannot mute a superior or matching rank.");
				// 	return 1;
				// }
				else if(user_exists) {
					_messageQueue.push(message);
				}

				return 1;









			case POKE:
				if(user_exists) {
					_messageQueue.push(message);
					if (arg_str == this_user) 	{storeMessage("             <SERVER> : You have uhh.. poked, yourself?");}
					else 					{storeMessage("             <SERVER> : You have poked " + arg_str + "!");}
				}
				else if (arg_str=="")		{storeMessage("             <SERVER> : Please enter the target user.");}
				else if (arg_str!="")		{storeMessage("             <SERVER> : " + arg_str + " is not online.");}
				return 1;








			case PM:
				if(!user_exists) {
					if (arg_str=="")		{storeMessage("             <SERVER> : Please enter the target user.");}
					else if (arg_str!="")	{storeMessage("             <SERVER> : " + arg_str + " is not online.");}
					return 1;
				}
				// else if(_user.getPriviledges() < ADMIN) {
				// 	storeMessage("             <SERVER> : Insufficient priviledges. (ADMIN only)");
				// 	return 1;
				// }
				else if (arg_str == this_user) {
					storeMessage("             <SERVER> : You cannot pm yourself.");
					return 1;
				}	
				// else if(_user.getPriviledges() <= arg_obj.getPriviledges()) {
				// 	storeMessage("             <SERVER> : You cannot mute a superior or matching rank.");
				// 	return 1;
				// }
				else if(arg_str2 == "") {
					storeMessage("             <SERVER> : Please enter a message.");
				}
				else {
					_messageQueue.push(message);
				}
				return 1;











			case EXIT:
				_messageQueue.push(message);
				return 1;












			case IGNORE:
				if(arg_str == "all") {
					_messageQueue.push(message);
				}
				else if(!user_exists) {
					if (arg_str=="")		{storeMessage("             <SERVER> : Please enter the target user.");}
					else if (arg_str!="")	{storeMessage("             <SERVER> : " + arg_str + " is not online.");}
					return 1;
				}
				else if(_user.getPriviledges() < ADMIN) {
					storeMessage("             <SERVER> : Insufficient priviledges. (ADMIN only)");
					return 1;
				}
				else if (arg_str == this_user) {
					storeMessage("             <SERVER> : You cannot mute yourself.");
					return 1;
				}	
				else if(_user.getPriviledges() <= arg_obj.getPriviledges()) {
					storeMessage("             <SERVER> : You cannot mute a superior or matching rank.");
					return 1;
				}
				else if(user_exists) {
					_messageQueue.push(message);
				}

				return 1;















			case TIMEOUT:
				if(arg_str == "all") {
					_messageQueue.push(message);
				}
				else if(!user_exists) {
					if (arg_str=="")		{storeMessage("             <SERVER> : Please enter the target user.");}
					else if (arg_str!="")	{storeMessage("             <SERVER> : " + arg_str + " is not online.");}
					return 1;
				}
				else if(_user.getPriviledges() < ADMIN) {
					storeMessage("             <SERVER> : Insufficient priviledges. (ADMIN only)");
					return 1;
				}
				else if (arg_str == this_user) {
					storeMessage("             <SERVER> : You cannot timeout yourself.");
					return 1;
				}	
				else if(_user.getPriviledges() <= arg_obj.getPriviledges()) {
					storeMessage("             <SERVER> : You cannot timeout a superior or matching rank.");
					return 1;
				}
				else if(user_exists) {
					_messageQueue.push(message);
				}

				// if(!ss.eof()) {
				// 	arg_str2 = "";
				// 	while(!ss.eof()) {
				// 		ss >> temp;
				// 		arg_str2 += temp + " ";
				// 	}
				// 	_messageQueue.push 				  		  ("             <SERVER> : Reason: " + arg_str2);
				// }
				return 1;












			case RELEASE:
				if(arg_str == "all") {
					_messageQueue.push(message);
				}
				else if(!user_exists) {
					if (arg_str=="")		{storeMessage("             <SERVER> : Please enter the target user.");}
					else if (arg_str!="")	{storeMessage("             <SERVER> : " + arg_str + " is not online.");}
					return 1;
				}
				else if(_user.getPriviledges() < ADMIN) {
					storeMessage("             <SERVER> : Insufficient priviledges. (ADMIN only)");
					return 1;
				}
				else if (arg_str == this_user) {
					storeMessage("             <SERVER> : You cannot untimeout yourself.");
					return 1;
				}	
				// else if(_user.getPriviledges() <= arg_obj.getPriviledges()) {
				// 	storeMessage("             <SERVER> : You cannot mute a superior or matching rank.");
				// 	return 1;
				// }
				else if(user_exists) {
					_messageQueue.push(message);
				}

				return 1;


			case SNAKE:
				snakeGame.run();
				_Gooey.showScreen(CHAT);
				return 1;




			default:
				cout << '\a';
				storeMessage("             <SERVER> : Command not recognized.");
				return 1;
		}
















	} //USER RECIEVED COMMAND
	else if(out_in == IN) {		
		switch(jj) {
			case HELP:
				//should never see
				return 1;


			case KICK:
				if((arg_str == this_user) || ((arg_str == "all")&&(_user.getPriviledges() < ADMIN))) {
					// show kick screen
					// call kick function
					endwin();
					exit(EXIT_SUCCESS);
					return 1;
				}
				storeMessage("             <SERVER> : " + user_str + " has kicked " + arg_str + ".");
				if(arg_str2 != "") {
					storeMessage("             <SERVER> : Reason: " + arg_str2);
				}

				removeUser(arg_str);									
				return 1;


			case MUTE:
				if((arg_str == this_user) || ((arg_str == "all")&&(_user.getPriviledges() < ADMIN))) {
					_user.setPriviledges(SPECTATOR);
				}
				storeMessage("             <SERVER> : " + user_str + " has muted " + arg_str + ".");
				if(arg_str2 != "") {
					storeMessage("             <SERVER> : Reason: " + arg_str2);
				}
				return 1;


			case UNMUTE:
				if((arg_str == this_user) || ((arg_str == "all")&&(_user.getPriviledges() < ADMIN))) {
					_user.setPriviledges(REGULAR);
				}
				storeMessage("             <SERVER> : " + user_str + " has unmuted " + arg_str + ".");
				return 1;


			case POKE:
				if(arg_str == this_user) {
					cout << '\a';
					if(arg_str != user_str) {storeMessage("             <SERVER> : You have been poked by " + user_str);}
				}
				return 1;	



			case PM:
				if(arg_str == this_user) {
					storeMessage("/yellow{/b{<" + user_str + "> : " + arg_str2 + "}}");
				}
				else if (user_str == this_user) {
					storeMessage("/cyan{/b{<" + user_str + "> : " + arg_str2 + "}}");
				}
				return 1;






			case EXIT:
				if(user_str == this_user) {
					endwin();
					exit(EXIT_SUCCESS);
				}
				removeUser(arg_str);									
				return 1;






			case IGNORE:
				// _messageQueue.push(message);
				return 1;







			case TIMEOUT:
				if((arg_str == this_user) || ((arg_str == "all")&&(_user.getPriviledges() < ADMIN))) {
					_user.setPriviledges(TIMEDOUT);
					_Gooey.printTimeout();
					// _messageQueue.push 				  		  ("             <SERVER> : " + user_str + " has unmuted " + arg_str + ".");
				}
				storeMessage("             <SERVER> : " + user_str + " has put " + arg_str + " in timeout.");
				if(arg_str2 != "") {
					storeMessage("             <SERVER> : Reason: " + arg_str2);
				}
				return 1;



			case RELEASE:
				if((arg_str == this_user) || ((arg_str == "all")&&(_user.getPriviledges() < ADMIN))) {
					_user.setPriviledges(REGULAR);
					_Gooey.printChat();
					// _messageQueue.push 				  		  ("             <SERVER> : " + user_str + " has unmuted " + arg_str + ".");
				}
				storeMessage("             <SERVER> : " + user_str + " has released " + arg_str + " from timeout.");
				return 1;	
		}
	}
	return 1;
}

