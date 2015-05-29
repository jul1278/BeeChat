/* Block.h
 * ENB241 Project
 *
 * Block class header
 *
 */

#ifndef _BLOCK_H
#define _BLOCK_H

#include <vector>								///< required for: 
#include <ncurses.h>							///< required for: 
using std::vector;	

const char BLOCKS = 'x';						///< the visual for blocks
const int START_BLOCKS = 0;						///< blacks spawned on startup

class Block
{
public:
	Block();									///< 
	~Block();									///< 
	Block(WINDOW **snake_scr);					///< 

	void setupBlocks(int xlim, int ylim);		///< 
	void spawnBlock(int snake_x, int snake_y);	///< 
	bool isBlock(int snake_x, int snake_y);		///< 
	void printBlocks();							///< 

// private:
	WINDOW **snake_win;							///< 
	vector<int> x;								///< 
	vector<int> y;								///< 
	vector<int> type;							///< 
};

#endif
