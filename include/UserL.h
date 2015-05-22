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

#define TIMEDOUT   -1
#define SPECTATOR	0
#define REGULAR		1
#define ADMIN		2
#define SADMIN		3

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
