/* User.h
 * ENB241 Project
 *
 * User class header
 *
 */

#ifndef _USERL_H
#define _USERL_H

#include <string>									///< required for: string operations
using std::string;

enum POWER {SPECTATOR, REGULAR, ADMIN, SADMIN};

class UserL
{
public:
	UserL(string username, int priviledges);		///< constructs a User object with given username and power
	UserL();										///< constructs a temporary User object
	~UserL();										///< deconstructs a User object

	string getUser();								///< returns the stored username
	int getSwears();								///< returns the swear count
	void incSwears();								///< incriments the swear count
	int getPriviledges();							///< returns the users power
	// void setPriviledges(int type);					///< sets the users power
	bool isMuted();
	bool isTimedout();
	void setMute(bool mute);
	void setTimeout(bool timeout);

private:
	bool _muted;
	bool _timeout;
	int _swearjar;									///< a count of each message the user has sworn in
	int _priviledges;								///< a measure of the users power/priviledges
	string _username;								///< the operators username
};



#endif
