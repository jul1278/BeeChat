/* theSnake.h
 * ENB241 Project
 *
 * theSnake class header
 *
 */

#ifndef _THE_SNAKE_H
#define _THE_SNAKE_H

#include <vector>
#include "ncurses.h"
using std::vector;

#define START_LENGTH 5

#define HEAD 'O'
#define BODY '@'
#define TAIL '.' 
#define PATH ' '

#define UP		-1
#define DOWN	1
#define LEFT	-2
#define RIGHT	2

class theSnake
{
public:
	theSnake();
	~theSnake();
	theSnake(WINDOW **snake_scr);

	void setupSnake(vector<int> block_x, vector<int> block_y);
	void moveSnake();	// move and print snake
	void growSnake();				// adds one to tail but prints next timestep; or
	void printSnake();				// print snake
	bool isSnake(int snake_x, int snake_y);

// private:
	WINDOW **snake_win;
	vector<int> x;
	vector<int> y;
	int _direction;
};

#endif
