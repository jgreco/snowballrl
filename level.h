#ifndef LEVEL_H_
#define LEVEL_H_

#include <stdint.h>

typedef struct level_str {
	int height, width;

	uint8_t **snow;
	uint8_t **trees;
} *level;

level make_level(int height, int width);
void pop_monsters(level map);

#endif
