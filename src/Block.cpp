/* Block.cpp
 * ENB241 Project
 *
 * Block class implementation
 *
 */
#include <random>
#include "Block.h"

Block::Block(WINDOW **snake_scr) {
	snake_win = snake_scr;
}

Block::Block() {

}

Block::~Block() {

}


void Block::setupBlocks(int xlim, int ylim) {
	int ii;
	for(ii = 0; ii < xlim; ii++) {
		x.push_back(ii);
		y.push_back(0);
	}
	for(ii = 0; ii < xlim; ii++) {
		x.push_back(ii);
		y.push_back(ylim-1);
	}
	for(ii = 0; ii < ylim; ii++) {
		x.push_back(0);
		y.push_back(ii);
	}
	for(ii = 0; ii < ylim; ii++) {
		x.push_back(xlim-1);
		y.push_back(ii);
	}
}

void Block::spawnBlock(int snake_x, int snake_y) {
	int chance = rand() % 1001;
	if(chance < 100) {
		x.push_back(snake_x);
		y.push_back(snake_y);
	}
}

void Block::printBlocks() {
	for(int ii = 0; ii < x.size(); ii++) {
		mvwaddch(*snake_win, y[ii], x[ii], BLOCKS);
	}
}	

bool Block::isBlock(int snake_x, int snake_y) {
	for(int ii = 0; ii < x.size(); ii++) {
		if(snake_x == x[ii]) {
			if(snake_y == y[ii]) {
				return 1;
			}
		}
	}
	return 0;
}
