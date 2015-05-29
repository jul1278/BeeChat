/* theSnake.h
 * ENB241 Project
 *
 * theSnake class header
 *
 */

#ifndef _THE_SNAKE_H
#define _THE_SNAKE_H

#include <vector>				///< required for: 
#include <ncurses.h>			///< required for: visuals
using std::vector;

const int START_LENGTH = 5;		///< the initial length of the snake

const char HEAD = 'O';			///< the visuals of the snake head
const char BODY = '@';			///< the visuals of the snake body
const char TAIL = '.'; 			///< the visuals of the snake tail
const char PATH = ' ';			///< the visuals of the snake path

/// simply used to make code more readable
enum DIR {UP = -1, DOWN = 1, LEFT = -2, RIGHT = 2, STILL = 0};

class theSnake
{
public:
	theSnake(WINDOW **snake_scr);									///< constructs and initializes a snake object
	theSnake();														///< constructs a temporary snake object
	~theSnake();													///< deconstructs a snake object

	void setupSnake(vector<int> block_x, vector<int> block_y);		///<
	bool isSnake(int snake_x, int snake_y);							///<
	void moveSnake();												///< move and print snake
	void growSnake();												///< adds one to tail but prints next timestep; or
	void printSnake();												///< print snake
	void printScore();												///< print score

// private:
	WINDOW **snake_win;												///< 
	vector<int> x;													///< 
	vector<int> y;													///< 
	DIR _direction;													///< 
};

#endif
