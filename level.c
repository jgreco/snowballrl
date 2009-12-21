#include "level.h"
#include "util.h"
#include <stdlib.h>
#include <stdint.h>

void snow(level map);
void trees(level map);

level make_level(int height, int width)
{
	int i;

	level new = (level)malloc(sizeof(struct level_str));

	new->height = height;
	new->width = width;


	new->snow = (uint8_t** )malloc(height * sizeof(uint8_t* ));
	new->trees = (uint8_t** )malloc(height * sizeof(uint8_t* ));

	for(i=0; i<width; i++) {
		new->snow[i] = (uint8_t* )malloc(width * sizeof(uint8_t));
		new->trees[i] = (uint8_t* )malloc(width * sizeof(uint8_t));
	}

	snow(new);
	trees(new);

	return new;
}

void snow(level map)
{
	int i, k;

	for(i=0; i<map->height; i++)
	for(k=0; k<map->width; k++)
		map->snow[i][k] = 3;
//		map->snow[i][k] = range(0, 4);

	return;
}

void trees(level map)
{
	int i, k;

	for(i=0; i<map->height; i++)
	for(k=0; k<map->width; k++)
		map->trees[i][k] = (range(0,20)==1);

	return;
}
