/* Block.h
 * ENB241 Project
 *
 * Block class header
 *
 */

#ifndef _BLOCK_H
#define _BLOCK_H

#include <vector>
#include "ncurses.h"
using std::vector;

#define BLOCKS 'x'
#define START_BLOCKS 0

class Block
{
public:
	Block();
	~Block();
	Block(WINDOW **snake_scr);

	void setupBlocks(int xlim, int ylim);
	void spawnBlock(int snake_x, int snake_y);
	void printBlocks();
	bool isBlock(int snake_x, int snake_y);

// private:
	WINDOW **snake_win;
	vector<int> x;
	vector<int> y;
	vector<int> type;
};

#endif
