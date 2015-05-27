/* theFood.cpp
 * ENB241 Project
 *
 * theFood class implementation
 *
 */

#include "snake/theFood.h"

theFood::theFood(int *xlim, int *ylim, WINDOW **snake_scr) {
	snake_win = snake_scr;
	x_lim = xlim;
	y_lim = ylim;

	x.reserve(50);
	y.reserve(50);
	age.reserve(50);
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
			age.push_back(0);
		}
	}
}

void theFood::growFood(vector<int> snake_x, vector<int> snake_y, vector<int> block_x, vector<int> block_y) {
	if(x.size() < MAX_FOOD) {
		int chance = rand() % 1001;
		if(chance < SPAWN_CHANCE) {
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
			age.push_back(0);
			// printFood();
		}
	}
}

void theFood::printFood() {
	wattron(*snake_win, A_BOLD);
	for(int ii = 0; ii < x.size(); ii++) {
		if(age[ii] < AGE_1) {
			wattron(*snake_win, COLOR_PAIR(2));
		}
		else if(age[ii] < AGE_2) {
			wattron(*snake_win, COLOR_PAIR(3));
		}
		else if(age[ii] < AGE_3) {
			wattron(*snake_win, COLOR_PAIR(1));
		}
		mvwaddch(*snake_win, y[ii], x[ii], FOOD);
	}
	wattrset(*snake_win, A_NORMAL);
}

int theFood::eatFood(int snake_x, int snake_y) {
	for(int ii = 0; ii < x.size(); ii++) {
		if(snake_x == x[ii]) {
			if(snake_y == y[ii]) {
				int _age = age[ii];
				x.erase(x.begin() + ii);
				y.erase(y.begin() + ii);
				age.erase(age.begin() + ii);
				if(age[ii] < AGE_1) {
					return VAL_1;
				}
				else if(age[ii] < AGE_2) {
					return VAL_2;
				}
				else if(age[ii] < AGE_3) {
					return VAL_3;
				}
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

void theFood::ageFood() {
	for(int ii = 0; ii < x.size(); ii++) {
		age[ii]++;
		if(age[ii] >= MAX_AGE) {
			mvwaddch(*snake_win, y[ii], x[ii], ' ');
			x.erase(x.begin() + ii);
			y.erase(y.begin() + ii);
			age.erase(age.begin() + ii);
		}
	}
}
