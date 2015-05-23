/* theFood.cpp
 * ENB241 Project
 *
 * theFood class implementation
 *
 */

#include "theFood.h"

theFood::theFood(int *xlim, int *ylim, WINDOW **snake_scr) {
	snake_win = snake_scr;
	x_lim = xlim;
	y_lim = ylim;

	x.reserve(50);
	y.reserve(50);
}

theFood::theFood() {

}

theFood::~theFood() {

}


void theFood::setupFood(vector<int> snake_x, vector<int> snake_y, vector<int> block_x, vector<int> block_y) {
	int skip = 0;
	while(x.size() < START_FOOD) {
		int xrand = rand() % (*x_lim-1) + 1;
		int yrand = rand() % (*y_lim-1) + 1;
		for(int ii = 0; ii < snake_x.size(); ii++) {
			if(snake_x[ii] == xrand) {
				if(snake_y[ii] == yrand) {
					skip = 1;
				}
			}
		}
		for(int ii = 0; ii < block_x.size(); ii++) {
			if(block_x[ii] == xrand) {
				if(block_y[ii] == yrand) {
					skip = 1;
				}
			}
		}
		if(skip) {
			skip = 0;
			continue;
		}
		else {
			x.push_back(xrand);
			y.push_back(yrand);
		}
	}
}

void theFood::growFood(vector<int> snake_x, vector<int> snake_y, vector<int> block_x, vector<int> block_y) {
	if(x.size() < MAX_FOOD) {
		int chance = rand() % 1001;
		if(chance < 20) {
			int xrand = rand() % (*x_lim-1) + 1; // 1->xlim
			int yrand = rand() % (*y_lim-1) + 1; // 1->xlim
			for(int ii = 0; ii < snake_x.size(); ii++) {
				if(snake_x[ii] == xrand) {
					if(snake_y[ii] == yrand) {
						return;
					}
				}
			}
			for(int ii = 0; ii < block_x.size(); ii++) {
				if(block_x[ii] == xrand) {
					if(block_y[ii] == yrand) {
						return;
					}
				}
			}
			x.push_back(xrand);
			y.push_back(yrand);
			printFood();
		}
	}
}

void theFood::printFood() {
	wattron(*snake_win, A_BOLD);
	wattron(*snake_win, COLOR_PAIR(3));
	for(int ii = 0; ii < x.size(); ii++) {
		mvwaddch(*snake_win, y[ii], x[ii], FOOD);
	}
	wattroff(*snake_win, COLOR_PAIR(3));
	wattroff(*snake_win, A_BOLD);
}

void theFood::eatFood(int snake_x, int snake_y) {
	for(int ii = 0; ii < x.size(); ii++) {
		if(snake_x == x[ii]) {
			if(snake_y == y[ii]) {
				x.erase(x.begin() + ii);
				y.erase(y.begin() + ii);
				return;
			}
		}
	}
}

bool theFood::isFood(int snake_x, int snake_y) {
	for(int ii = 0; ii < x.size(); ii++) {
		if(snake_x == x[ii]) {
			if(snake_y == y[ii]) {
				return 1;
				// could impl eat food here, but less versitile
			}
		}
	}
	return 0;
}
