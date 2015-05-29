/* theSnake.cpp
 * ENB241 Project
 *
 * theSnake class implementation
 *
 */

#include "snake/theSnake.h"


theSnake::theSnake(WINDOW **snake_scr) {
	snake_win = snake_scr;
	_direction = STILL;
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
	if(_direction == STILL) {
		return;
	}
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

bool theSnake::isSnake(int snake_x, int snake_y) {	//ignores head
	for(int ii = 1; ii < x.size(); ii++) {
		if(snake_x == x[ii]) {
			if(snake_y == y[ii]) {
				return 1;
			}
		}
	}
	return 0;
}

void theSnake::printSnake() {
	wattron(*snake_win, COLOR_PAIR(2));
	mvwaddch(*snake_win, y.front(), x.front(), HEAD);
	for(int ii = 1; ii < x.size()-1; ii++) {
		mvwaddch(*snake_win, y[ii], x[ii], BODY);
	}
	mvwaddch(*snake_win, y.back(), x.back(), TAIL);
	wattroff(*snake_win, COLOR_PAIR(2));
}

void theSnake::printScore() {
	int score = x.size() - START_LENGTH;
	wattron(*snake_win, COLOR_PAIR(6));
	mvwprintw(*snake_win, 1,1, "SCORE: %d", score);
	wattroff(*snake_win, COLOR_PAIR(6));
}
