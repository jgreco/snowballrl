#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "snowballrl.h"

void ninterface();
void draw();

int offset_x;
int offset_y;

int main()
{
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	start_color();
	use_default_colors();

	assume_default_colors(COLOR_WHITE, COLOR_BLACK);

	srand(time(NULL));

	map = make_level(1000,1000);
	player = create_monster(PLAYER);
	player->x = 500;
	player->y = 500;

	offset_x = 0;
	offset_y = 0;

	ninterface();

	endwin();

	return 0;
}

void ninterface()
{
	int key=0;


	while(1) {
		draw();
		key = getch();

		switch(key) {
			case KUP:
				move_mon(player, UP, map);
				break;
			case KDOWN:
				move_mon(player, DOWN, map);
				break;
			case KLEFT:
				move_mon(player, LEFT, map);
				break;
			case KRIGHT:
				move_mon(player, RIGHT, map);
				break;
			case KUPLEFT:
				move_mon(player, UPLEFT, map);
				break;
			case KUPRIGHT:
				move_mon(player, UPRIGHT, map);
				break;
			case KDOWNLEFT:
				move_mon(player, DOWNLEFT, map);
				break;
			case KDOWNRIGHT:
				move_mon(player, DOWNRIGHT, map);
				break;


			case KEY_UP:
				offset_y = offset_y - 10;
				break;
			case KEY_DOWN:
				offset_y = offset_y + 10;
				break;
			case KEY_LEFT:
				offset_x = offset_x - 10;
				break;
			case KEY_RIGHT:
				offset_x = offset_x + 10;
				break;


			case 'Q':
				return;
		}
	}

	return;
}

void draw()
{
	int y, x;

	erase();

	offset_x = player->x - (COLS / 2);
	offset_y = player->y - (LINES / 2);

	for(y=0; y<LINES; y++)
	for(x=0; x<COLS; x++) {
		if(x+offset_x < 0 || x+offset_x >= map->width
			|| y+offset_y < 0 || y+offset_y >= map->height)
			continue;

		if(map->trees[y+offset_y][x+offset_x])
			mvprintw(y, x, "&");
	}

	mvprintw(player->y-offset_y, player->x-offset_x, "@");

	refresh();
}
