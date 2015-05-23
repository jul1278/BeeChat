/* theFood.h
 * ENB241 Project
 *
 * theFood class header
 *
 */

#ifndef _THE_FOOD_H
#define _THE_FOOD_H

#include <vector>
#include "ncurses.h"
#include <cstdlib>
using std::vector;

#define FOOD 'o'
#define START_FOOD 5
#define MAX_FOOD 10

class theFood
{
public:
	theFood();
	~theFood();
	theFood(int *xlim, int *ylim, WINDOW **snake_scr);

	void growFood(vector<int> snake_x, vector<int> snake_y, vector<int> block_x, vector<int> block_y);				// food cant spawn on snake blocks or walls
	void setupFood(vector<int> snake_x, vector<int> snake_y, vector<int> block_x, vector<int> block_y);
	void printFood();				// check to spawn food + update new food only
	void eatFood(int snake_x, int snake_y);
	bool isFood(int snake_x, int snake_y);

// private:
	WINDOW **snake_win;
	vector<int> x;
	vector<int> y;
	int *x_lim;
	int *y_lim;
};

#endif
