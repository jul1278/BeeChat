/* Snake.h
 * ENB241 Project
 *
 * Snake class header
 *
 */

#ifndef _SNAKE_H
#define _SNAKE_H

#include <stdio.h>      		///< required for: 
#include <stdlib.h>     		///< required for: 
#include <time.h>				///< required for: seed
#include <unistd.h>				///< required for: random
#include "theSnake.h"	
#include "theFood.h"	
#include "Block.h"		

const int STEP_VERT = 50000;	///< step constant for the vertical direction
const int STEP_HORI = 30000;	///< step constant for the horizontal direction
const char PAUSE_BRICK = 'X';	///< the filler brick for pause screen

class Snake
{
public:
	Snake();					///< creates a snake object
	~Snake();					///< deconstructs a snake object
	int run();					///< initializes then runs snake

private:
	void initSnake();			///< setup screen + draw elements
	bool userInput();			///< pause + change direction

	bool timeStep();			///< move snake + check if dead + check if on food + check food spawn
	void printEnd();			///< print animation
	bool Pause();				///< print pause screen

	WINDOW *snake_win;			///< the snake window
	theSnake _snake;			///< the snake
	theFood _food;				///< the food
	Block _blocks;				///< the walls
	int x_lim;					///< the size (x) of the snake window
	int y_lim;					///< the size (y) of the snake window
};



#endif


// TASKS:
// food colours (snake colour is last food?)
// cant access snake.x directly



// FOOD:
// normal
// double score -- diff colour
// double food  -- diff colour, flashing.

// EXTENDED:
// operator overload + for growth or position
// inheritance for game->snake or bmtron
// templates everywhere
// exceptions nowhere


















	// void printField();				// print snake + food
