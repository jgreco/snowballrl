#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "snowballrl.h"
#include "arraylist.h"

#define TREECOLOR 70
#define PLAYERCOLOR COLOR_BLUE

void ninterface();
void draw();
void collect_snow();

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

	init_pair(1, COLOR_BLUE, 144);/*COLOR_BLACK); */
	init_pair(2, COLOR_BLUE, 186);/*238); */
	init_pair(3, COLOR_BLUE, 187);/*245); */
	init_pair(4, COLOR_BLUE, COLOR_WHITE);


	init_pair(5, TREECOLOR, 144);/*COLOR_BLACK); */
	init_pair(6, TREECOLOR, 186);/*238); */
	init_pair(7, TREECOLOR, 187);/*245); */
	init_pair(8, TREECOLOR, COLOR_WHITE);

	init_pair(9, -1, COLOR_BLUE);
	init_pair(10, -1, COLOR_RED);

	assume_default_colors(COLOR_WHITE, COLOR_BLACK);

	srand(time(NULL));

	map = make_level(1000,1000);
	player = create_monster(PLAYER);
	player->x = 500;
	player->y = 500;
	player->hp = 100;
	snow_count = 10;

	offset_x = 0;
	offset_y = 0;

	messages = al_makenull(NULL);

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

			case ',':
				collect_snow();
				break;

			case ' ':
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
	int color;
	void *dumb;
	int snowbar, hpbar;

	erase();

	offset_x = player->x - (COLS / 2);
	offset_y = player->y - (LINES / 2);

	for(y=0; y<LINES; y++)
	for(x=0; x<COLS; x++) {
		if(x+offset_x < 0 || x+offset_x >= map->width
			|| y+offset_y < 0 || y+offset_y >= map->height)
			continue;

		color = map->snow[y+offset_y][x+offset_x] + 1;

		if(map->trees[y+offset_y][x+offset_x]) {
			mvprintw(y, x, "&");
			mvchgat(y, x, 1, COLOR_PAIR(color+4) | A_BOLD, color+4, dumb);
		} else
			mvchgat(y, x, 1, COLOR_PAIR(color), color, dumb);
	}

	color = map->snow[player->y][player->x] + 1;
	mvprintw(player->y-offset_y, player->x-offset_x, "@");
	mvchgat(player->y-offset_y, player->x-offset_x, 1, COLOR_PAIR(color)|A_BOLD, color, dumb);


	for(x = al_first(monsters); x != al_end(monsters); x = al_next(x, monsters)) {
		monster curr = (monster)al_retrieve(x, monsters);
		ai(curr);

		if(curr->hidden)
			continue;

		color = map->snow[curr->y][curr->x] + 1;

		mvprintw(curr->y-offset_y, curr->x-offset_x, "%c", curr->symbol);
		mvchgat(curr->y-offset_y, curr->x-offset_x, 1, COLOR_PAIR(color)|A_BOLD, color, dumb);
	}



	snowbar = (double)(LINES+1) * ((double)snow_count / (double)100);
	hpbar = (double)(LINES+1) * ((double)player->hp / (double)100);

	for(y=0; y<snowbar; y++) {
		mvprintw(LINES-y, 0, " ");
		mvchgat(LINES-y, 0, 1, COLOR_PAIR(9), 9, dumb);
	}

	for(y=0; y<hpbar; y++) {
		mvprintw(LINES-y, 1, " ");
		mvchgat(LINES-y, 1, 1, COLOR_PAIR(10), 10, dumb);
	}

	while(!al_empty(messages)) {
		mvprintw(0, 2, "%s", al_retrieve(al_first(messages),messages));
		al_delete(al_first(messages), messages);
		if(!al_empty(messages))
			getch();
	}

	refresh();
}

void collect_snow()
{
	int i;
	int x, y;
	int collected = 0;

	if(map->snow[player->y][player->x] > 0) {
		map->snow[player->y][player->x]--;
		collected++;
	}

	for(i=0; i<4; i++) {
		x = player->x;
		y = player->y;
		move_coord(&x, &y, range(0, 9));
		if(map->snow[y][x] > 0) {
			map->snow[y][x]--;
			collected++;
		}
	}

	snow_count += collected;

	if(snow_count > 100)
		snow_count = 100;

	return;
}
