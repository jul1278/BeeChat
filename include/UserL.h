/* User.h
 * ENB241 Project
 *
 * User class header
 *
 */

#ifndef _USERL_H
#define _USERL_H

#include <string>
using std::string;

enum POWER {SPECTATOR, REGULAR, ADMIN, SADMIN, TIMEDOUT = -1};

class UserL
{
public:
	UserL(string username, int priviledges);
	UserL();
	~UserL();

	string getUser();
	int getSwears();
	void incSwears();
	int getPriviledges();
	void setPriviledges(int type);

private:
	int _swearjar;
	int _priviledges;
	string _username;
};



#endif
