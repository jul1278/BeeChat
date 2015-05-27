/* Snake.h
 * ENB241 Project
 *
 * Snake class header
 *
 */

#ifndef _SNAKE_H
#define _SNAKE_H

#include <stdio.h>      // required for: 
#include <stdlib.h>     // required for: 
#include <time.h>		// required for: seed
#include <unistd.h>		// required for: random
#include "theSnake.h"	
#include "theFood.h"	
#include "Block.h"		

#define STEP_VERT 50000
#define STEP_HORI 30000
#define PAUSE_BRICK 'X'

class Snake
{
public:
	Snake();
	~Snake();
	int run();						// setup then - user input, timestep, delay

private:
	void initSnake();				// setup screen + draw elements
	void userInput();				// pause + change direction

	int timeStep();					// move snake + check if dead + check if on food + check food spawn
	void printEnd();				// print animation
	void Pause();					// print pause screen

	WINDOW *snake_win;
	theSnake _snake;
	theFood _food;
	Block _blocks;
	int x_lim;
	int y_lim;
};



#endif


// TASKS:
// food colours (snake colour is last food?)
// grow size (loop grow)

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
