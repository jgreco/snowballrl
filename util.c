#include "util.h"
#include <stdlib.h>

int range(int lower, int upper)
{
	return lower + rand() % (upper - lower);
}

void move_coord(int *x, int *y, DIRECTION dir)
{
	switch(dir) {
		case UP:
			(*y)--;
			break;
		case DOWN:
			(*y)++;
			break;
		case LEFT:
			(*x)--;
			break;
		case RIGHT:
			(*x)++;
			break;
		case UPLEFT:
			(*y)--;
			(*x)--;
			break;
		case UPRIGHT:
			(*y)--;
			(*x)++;
			break;
		case DOWNLEFT:
			(*y)++;
			(*x)--;
			break;
		case DOWNRIGHT:
			(*y)++;
			(*x)++;
			break;
	}
}
