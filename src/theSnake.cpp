/* theSnake.cpp
 * ENB241 Project
 *
 * theSnake class implementation
 *
 */

#include "theSnake.h"


theSnake::theSnake(WINDOW **snake_scr) {
	snake_win = snake_scr;
	_direction = RIGHT;
	x.reserve(50);
	y.reserve(50);
}

theSnake::theSnake() {
	
}

theSnake::~theSnake() {

}


void theSnake::setupSnake(vector<int> block_x, vector<int> block_y) {
	for(int ii = 0; ii < START_LENGTH; ii++) {
		x.push_back(START_LENGTH-ii+5);
		y.push_back(5);
	}
}

void theSnake::moveSnake() {
	if(_direction == UP || _direction == DOWN) {
		x.insert(x.begin(),x.front());
		y.insert(y.begin(),y.front()+_direction);
	}
	else {
		x.insert(x.begin(),x.front()+_direction/2);
		y.insert(y.begin(),y.front());
	}
	mvwaddch(*snake_win, y.back(), x.back(), PATH);
	x.erase(x.end()-1);
	y.erase(y.end()-1);

	// printSnake();
}	

void theSnake::growSnake() {
	// insert last element of value back()
	x.push_back(x.back());
	y.push_back(y.back());
}	

void theSnake::printSnake() {
	mvwaddch(*snake_win, y.front(), x.front(), HEAD);
	for(int ii = 1; ii < x.size()-1; ii++) {
		mvwaddch(*snake_win, y[ii], x[ii], BODY);
	}
	mvwaddch(*snake_win, y.back(), x.back(), TAIL);
}	

