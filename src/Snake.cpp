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
	// nodelay(snake_win,1);
	// halfdelay(1);

	_snake = theSnake(&snake_win);
	_food = theFood(&x_lim, &y_lim, &snake_win);
	_blocks = Block(&snake_win);
	initSnake();
}

Snake::~Snake() {

}

void Snake::initSnake() {
	noecho();
	curs_set(0);

	snake_win = newwin(y_lim, x_lim, 0, 0);
    // wborder(snake_win, 		'|', '|', '-','-','+','+','+','+');
    keypad(snake_win, TRUE);

    _blocks.setupBlocks(x_lim, y_lim);
    _snake.setupSnake(_blocks.x, _blocks.y);
    _food.setupFood(_snake.x, _snake.y, _blocks.x, _blocks.y);

    _snake.printSnake();
    _food.printFood();
    _blocks.printBlocks();
    // run();
}	

void Snake::userInput() {
	int c = wgetch(snake_win);
	if(c == 'P') {
		sleep(2);
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

void Snake::run() {
	cbreak();
	nodelay(snake_win,1);
	while(1) {
		userInput();
		// int c = wgetch(snake_win);
		if(timeStep()) {
			break;
		}

		if(_snake._direction == UP || _snake._direction == DOWN) {
			usleep(50000);
		}
		else {
			usleep(30000);
		}
	}
}


bool Snake::timeStep() {
	// move snake + check if dead + check if on food + check food spawn
	_snake.moveSnake();

	if(_food.isFood(_snake.x.front(), _snake.y.front())) {
		_food.eatFood(_snake.x.front(), _snake.y.front());
		_snake.growSnake();
		_blocks.spawnBlock(_snake.x.back(), _snake.y.back());
	}
	else if(_blocks.isBlock(_snake.x.front(), _snake.y.front())) {
		printEnd();
		return 1;
	}
	else if(_snake.isSnake(_snake.x.front(), _snake.y.front())) {
		printEnd();
		return 1;
	}

	_food.growFood(_snake.x, _snake.y, _blocks.x, _blocks.y);
	_blocks.printBlocks();
	_snake.printSnake();
	// growFood prints if grown
	// Blocks prints if grown
	wrefresh(snake_win);
	return 0;
}	


void Snake::printEnd() {

}	

