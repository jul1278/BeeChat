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
#define SPAWN_CHANCE 30 // 0->1000
#define START_FOOD 5
#define MAX_FOOD 10

#define AGE_1 60
#define AGE_2 120
#define AGE_3 200
#define MAX_AGE 200

#define VAL_1 7
#define VAL_2 5
#define VAL_3 1

class theFood
{
public:
	theFood();
	~theFood();
	theFood(int *xlim, int *ylim, WINDOW **snake_scr);

	void growFood(vector<int> snake_x, vector<int> snake_y, vector<int> block_x, vector<int> block_y);				// food cant spawn on snake blocks or walls
	void setupFood(vector<int> snake_x, vector<int> snake_y, vector<int> block_x, vector<int> block_y);
	void printFood();				// check to spawn food + update new food only
	void ageFood();
	int eatFood(int snake_x, int snake_y);
	bool isFood(int snake_x, int snake_y);

// private:
	WINDOW **snake_win;
	vector<int> x;
	vector<int> y;
	vector<int> age;
	// vector<int> growth;
	// vector<int> score;
	int *x_lim;
	int *y_lim;
};

#endif
