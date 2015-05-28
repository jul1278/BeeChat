/* theFood.h
 * ENB241 Project
 *
 * theFood class header
 *
 */

#ifndef _THE_FOOD_H
#define _THE_FOOD_H

#include <vector>			///< required for:
#include "ncurses.h"		///< required for:
#include <cstdlib>			///< required for:
using std::vector;

#define FOOD 'o'			///< the visuals for food
#define SPAWN_CHANCE 30 	///< chance to spawn foor, range: 0->1000
#define START_FOOD 5		///< food spawned at startup
#define MAX_FOOD 10			///< maximum amount of food

#define AGE_1 60			///< steps until first age
#define AGE_2 120			///< steps until second age
#define AGE_3 200			///< steps until decay
#define MAX_AGE 200			///< steps until decay

#define VAL_1 7				///< the amount of growth from age_1
#define VAL_2 5				///< the amount of growth from age_2
#define VAL_3 1				///< the amount of growth from age_3

class theFood
{
public:
	theFood();																								///< 
	~theFood();																								///< 
	theFood(int *xlim, int *ylim, WINDOW **snake_scr);														///< 

	void growFood(vector<int> snake_x, vector<int> snake_y, vector<int> block_x, vector<int> block_y);		///< food cant spawn on snake blocks or walls
	void setupFood(vector<int> snake_x, vector<int> snake_y, vector<int> block_x, vector<int> block_y);		///< 
	void printFood();																						///< check to spawn food + update new food only
	void ageFood();																							///< 
	int eatFood(int snake_x, int snake_y);																	///< 
	bool isFood(int snake_x, int snake_y);																	///< 

// private:
	WINDOW **snake_win;		///< 
	vector<int> x;			///< 
	vector<int> y;			///< 
	vector<int> age;		///< 
	// vector<int> growth;
	// vector<int> score;
	int *x_lim;				///< 
	int *y_lim;				///< 
};

#endif
