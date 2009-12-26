#include "monster.h"
#include "util.h"
#include "snowballrl.h"

#include <stdlib.h>
#include <math.h>

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
	new->hidden = 0;

	if(type == SLIZARD) {
		new->symbol = 'z';
		new->hidden = 1;
	} else if(type == SMAN)
		new->symbol = '8';

	return new;
}

int move_mon(monster mon, DIRECTION dir, level map)
{
	int x, y;
	int i;

	x = mon->x;
	y = mon->y;

	move_coord(&x, &y, dir);

	if(y < 0 || y >= map->height || x < 0 || x >= map->width)
		return 0;

	if(map->trees[y][x])
		return 0;

	if(player->x == x && player->y == y) {
		switch(mon->type) {
			case SLIZARD:
				al_insert(strdup("The snowlizard attacks you!"), al_end(messages), messages);
				player->hp = player->hp - 3;
				break;
			case SMAN:
				al_insert(strdup("The snowman attacks you!"), al_end(messages), messages);
				player->hp = player->hp - 2;
				break;
			case PLAYER:
				break;
		}

		return 0;
	}

	for(i=al_first(monsters); i != al_end(monsters); i = al_next(i, monsters)) {
		monster curr = (monster)al_retrieve(i, monsters);
		if(curr->x == x && curr->y == y) {
			return 0;
		}
	}

	mon->x = x;
	mon->y = y;

	return 0;
}

void ai(monster mon)
{
	if(mon->type == SLIZARD) {
		int x_dist = abs(mon->x - player->x);
		int y_dist = abs(mon->y - player->y);

		if(mon->hidden) {
			if(sqrt(x_dist*x_dist + y_dist*y_dist) < 3) {
				mon->hidden = 0;
				switch(range(0,2)) {
					case 0:
						al_insert(strdup("A snow lizard lunges out of the snow!"), al_end(messages), messages);
						break;
					case 1:
						al_insert(strdup("A snow lizard appears!"), al_end(messages), messages);
						break;
				}
			}
		} else {
			if(x_dist >= y_dist) {
				if(mon->x > player->x)
					move_mon(mon, LEFT, map);
				else
					move_mon(mon, RIGHT, map);
			} else if(x_dist < y_dist) {
				if(mon->y > player->y)
					move_mon(mon, UP, map);
				else
					move_mon(mon, DOWN, map);
			}
		}
	}

	return;
}
