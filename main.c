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

	ninterface();
}

void ninterface()
{
	int key=0;

	while(1) {
		key = getch();

		switch(key) {
			case KUP:
				move_mon(player, UP);
			case KDOWN:
				move_mon(player, DOWN);
			case KLEFT:
				move_mon(player, LEFT);
			case KRIGHT:
				move_mon(player, RIGHT);
			case KUPLEFT:
				move_mon(player, UPLEFT);
			case KUPRIGHT:
				move_mon(player, UPRIGHT);
			case KDOWNLEFT:
				move_mon(player, DOWNLEFT);
			case KDOWNRIGHT:
				move_mon(player, DOWNRIGHT);
		}
}
