#ifndef MONSTER_H_
#define MONSTER_H_

#include "util.h"
#include "level.h"

typedef enum { PLAYER, SLIZARD, SMAN } MON_TYPE;

typedef struct monster_str {
	MON_TYPE type;

	int hp;
	int x, y;
} *monster;

monster create_rand_mon();
monster create_monster(MON_TYPE type);
int move_mon(monster mon, DIRECTION dir, level map);

#endif
