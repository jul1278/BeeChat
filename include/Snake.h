/* Snake.h
 * ENB241 Project
 *
 * Snake class header
 *
 */

#ifndef _SNAKE_H
#define _SNAKE_H

#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>
#include <unistd.h>
#include "theSnake.h"
#include "theFood.h"
#include "Block.h"

#define STEP_SPEED 5

class Snake
{
public:
	Snake();
	~Snake();
	void run();

private:
	void initSnake();				// setup screen + draw snake + draw food
	void userInput();				// check for exit + pause + move

	bool timeStep();				// move snake + check if dead + check if on food + check food spawn
	void printStep();
	void printEnd();				// print win/lose screen

	WINDOW *snake_win;
	theSnake _snake;
	theFood _food;
	Block _blocks;
	int x_lim;
	int y_lim;
};



#endif


// TASKS:
// add score
// print score after loss
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
