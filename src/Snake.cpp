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

int Snake::run() {
	cbreak();
	nodelay(snake_win,1);
	while(1) {
		userInput();
		// int c = wgetch(snake_win);
		if(timeStep()) {
			return (_snake.x.size() - START_LENGTH);
		}

		if(_snake._direction == UP || _snake._direction == DOWN) {
			usleep(50000);
		}
		else {
			usleep(30000);
		}
	}
}


int Snake::timeStep() {
	// move snake + check if dead + check if on food + check food spawn
	_snake.moveSnake();

	if(_food.isFood(_snake.x.front(), _snake.y.front())) {
		int worth = _food.eatFood(_snake.x.front(), _snake.y.front());
		for(int ii = 0; ii < worth; ii++) {
			_snake.growSnake();
		}
		_blocks.spawnBlock(_snake.x[1], _snake.y[1]);
	}
	else if(_blocks.isBlock(_snake.x.front(), _snake.y.front())) {
		printEnd();
		return 1;
	}
	else if(_snake.isSnake(_snake.x.front(), _snake.y.front())) {
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
		// for(int ii = 1; ii < x_lim-1; ii++) {
		// 	mvwaddch(snake_win, 1, ii, BODY);
		// }
		// for(int ii = 2; ii < y_lim-1; ii++) {
		// 	mvwaddch(snake_win, ii, x_lim-2, BODY);
		// }
		// for(int ii = x_lim-2; ii > 0; ii--) {
		// 	mvwaddch(snake_win, y_lim-2, ii, BODY);
		// }
		// for(int ii = ylim-1; ii > 1; ii--) {
		// 	mvwaddch(snake_win, ii, 1, BODY);
		// }
