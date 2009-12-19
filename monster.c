#include "monster.h"

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

int move_mon(monster mon, DIRECTION direction, level map)
{

}
