/* User.cpp
 * ENB241 Project
 *
 * User class implementation
 *
 */

#include "UserL.h"

UserL::UserL(string username, int priviledges) {
	// ensure other classes make sure the username isnt already used
	_muted = 0;
	_timeout = 0;
	_swearjar = 0;
	_username = username;
	_priviledges = priviledges;
}

UserL::UserL() {

}

UserL::~UserL() {

}

string UserL::getUser() {
	return _username;
}

int UserL::getSwears() {
	return _swearjar;
}

void UserL::incSwears() {
	_swearjar++;
}


int UserL::getPriviledges() {
	return _priviledges;
}

// void UserL::setPriviledges(int type) {
// 	// if(power > ADMIN) {
// 		_priviledges = type;
// 	// 	return 1;
// 	// }
// 	// return 0;
// }

bool UserL::isMuted() {
	return _muted;
}

bool UserL::isTimedout() {
	return _timeout;
}

void UserL::setMute(bool mute) {
	_muted = mute;
}

void UserL::setTimeout(bool timeout) {
	_timeout = timeout;
}

