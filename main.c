#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "snowballrl.h"

void ninterface();

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

	player = create_monster(PLAYER);
	map = make_level(20,20);

	ninterface();

	return 0;
}

void ninterface()
{
	int key=0;

	while(1) {
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
		}
	}

	return;
}
