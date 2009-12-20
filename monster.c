#include "monster.h"
#include "util.h"

#include <stdlib.h>

monster create_rand_mon()
{
	int choice = range(0, 2);

	if(choice)
		return create_monster(SLIZARD);

	return create_monster(SMAN);
}

monster create_monster(MON_TYPE type)
{
	monster new = (monster)malloc(sizeof(struct monster_str));
	new->type = type;

	return new;
}

int move_mon(monster mon, DIRECTION dir, level map)
{
	int x, y;

	x = mon->x;
	y = mon->y;

	switch(dir) {
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UPLEFT:
			y--;
			x--;
			break;
		case UPRIGHT:
			y--;
			x++;
			break;
		case DOWNLEFT:
			y++;
			x--;
			break;
		case DOWNRIGHT:
			y++;
			x++;
			break;
	}

	if(!map->trees[y][x]) {
		mon->x = x;
		mon->y = y;
	}

	return 0;
}
