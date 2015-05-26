/* Snake.cpp
 * ENB241 Project
 *
 * Snake class implementation
 *
 */

#include "Snake.h"

Snake::Snake() {
	srand(time(NULL));
	getmaxyx(stdscr, y_lim, x_lim);

	_blocks = Block(&snake_win);
	_snake = theSnake(&snake_win);
	_food = theFood(&x_lim, &y_lim, &snake_win);
}

Snake::~Snake() {

}

void Snake::initSnake() {
	raw();
	noecho();
	curs_set(0);

	snake_win = newwin(y_lim, x_lim, 0, 0);
    keypad(snake_win, TRUE);
	nodelay(snake_win,1);

    _blocks.setupBlocks(x_lim, y_lim);
    _snake.setupSnake(_blocks.x, _blocks.y);
    _food.setupFood(_snake.x, _snake.y, _blocks.x, _blocks.y);

    _snake.printSnake();
    _food.printFood();
    _blocks.printBlocks();
}	

void Snake::userInput() {
	int c = wgetch(snake_win);
	if(c == 'p') {
		Pause();
	}
	else if(c == KEY_UP && _snake._direction != DOWN) {				//use setter (setDir), ensure you cant reverse
		_snake._direction = UP;
	}
	else if(c == KEY_DOWN && _snake._direction != UP) {
		_snake._direction = DOWN;
	}
	else if(c == KEY_LEFT && _snake._direction != RIGHT) {
		_snake._direction = LEFT;
	}
	else if(c == KEY_RIGHT && _snake._direction != LEFT) {
		_snake._direction = RIGHT;
	}
}	

int Snake::run() {
	initSnake();
	while(1) {
		userInput();

		if(timeStep()) {
			return (_snake.x.size() - START_LENGTH);	//score
		}

		if(_snake._direction == UP || _snake._direction == DOWN) {
			usleep(STEP_VERT);
		}
		else {
			usleep(STEP_HORI);
		}
	}
}


int Snake::timeStep() {
	// move snake + check if dead + check if on food + check food spawn
	_snake.moveSnake();
	int x = _snake.x.front();
	int y = _snake.y.front();

	if(_food.isFood(x, y)) {
		int worth = _food.eatFood(x, y);
		for(int ii = 0; ii < worth; ii++) {
			_snake.growSnake();
		}
		_blocks.spawnBlock(_snake.x[1], _snake.y[1]);
	}
	else if(_blocks.isBlock(x, y)) {
		printEnd();
		return 1;
	}
	else if(_snake.isSnake(x, y)) {
		printEnd();
		return 1;
	}

	_food.ageFood();
	_food.growFood(_snake.x, _snake.y, _blocks.x, _blocks.y);
	_food.printFood();
	_blocks.printBlocks();
	_snake.printScore();
	_snake.printSnake();
	// growFood prints if grown
	// Blocks prints if grown
	wrefresh(snake_win);
	return 0;
}	


void Snake::printEnd() {
	// 1,1 			 -> 1,xlim-2
	// 2,xlim-2 	 -> ylim-2,xlim-2
	// ylim-2,xlim-3 -> ylim-2,1
	// ylim-3,1      -> 2,1

	// 2,2 			 -> 2,xlim-3
	// 3,xlim-3 	 -> ylim-3,xlim-3
	// ylim-3,xlim-4 -> ylim-3,2
	// ylim-4,2      -> 3,2
	for(int loop = 0; loop < y_lim/2+1; loop++) {
		for(int ii = 1+loop; ii < x_lim-1-loop; ii++) {
			mvwaddch(snake_win, 1+loop, ii, BODY);
			wrefresh(snake_win);
			if(ii%15 == 0) {
				usleep(100);
			}
		}
		for(int ii = 2+loop; ii < y_lim-1-loop; ii++) {
			mvwaddch(snake_win, ii, x_lim-2-loop, BODY);
			wrefresh(snake_win);
			if(ii%15 == 0) {
				usleep(200);
			}
		}
		for(int ii = x_lim-3-loop; ii > loop; ii--) {
			mvwaddch(snake_win, y_lim-2-loop, ii, BODY);
			wrefresh(snake_win);
			if(ii%15 == 0) {
				usleep(100);
			}
		}
		for(int ii = y_lim-3-loop; ii > 1+loop; ii--) {
			mvwaddch(snake_win, ii, 1+loop, BODY);
			wrefresh(snake_win);
			if(ii%15 == 0) {
				usleep(200);
			}
		}
	}
}	

void Snake::Pause() {
	while(wgetch(snake_win) != 'p');
}
