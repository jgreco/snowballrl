#include "level.h"
#include "util.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "monster.h"
#include "snowballrl.h"

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
	pop_monsters(new);

	return new;
}

void pop_monsters(level map)
{
	int i;
	int area = map->height * map->width;

	int num_monsts = 0.03 * area;

	monsters = al_makenull(NULL);

	for(i=0; i<num_monsts; i++) {
		monster new = create_rand_mon();
		al_insert(new, al_first(monsters), monsters);

		new->x = range(0, map->width);
		new->y = range(0, map->height);
	}

	return;
}

void snow(level map)
{
	int num = 4;
	int k, i, x, y;
	double ***noise_funcs;
	int *noise_sizes;

	noise_funcs = (double*** )malloc(sizeof(double** ) * num);
	noise_sizes = (int* )malloc(sizeof(int) * num);

	noise_sizes[0] = map->height / 20;
	noise_sizes[1] = map->height / 15;
	noise_sizes[2] = map->height / 10;
	noise_sizes[3] = map->height / 5;
//	noise_sizes[4] = map->height / 2;

	for(k=0; k<num; k++) {
		i = noise_sizes[k];
		noise_funcs[k] = (double** )malloc(sizeof(double* ) * i);

		for(x=0; x<i; x++)
			noise_funcs[k][x] = (double* )malloc(sizeof(double) * i);
	}


	for(i=0; i<num; i++)
	for(y=0; y<noise_sizes[i]; y++)
	for(x=0; x<noise_sizes[i]; x++)
		noise_funcs[i][y][x] = (double)rand() / (double)RAND_MAX;


	for(y=0; y<map->height; y++) {
	for(x=0; x<map->width; x++) {
		map->snow[y][x] = 3;
		double temp = 0;

		/* add up the noise functions */
		for(i=0; i<num; i++) {
			double mult = (double)(map->height) / (double)(noise_sizes[i] - 2);
			int j;

			for(j=0; j*mult <= y; j++);
			for(k=0; k*mult <= x; k++);
			j--;
			k--;

#define NOISE(x,y) noise_funcs[i][y][x]

			int y1 = j*mult;
			int x2 = (k+1)*mult;
			int y2 = (j+1)*mult;
			int x1 = k*mult;

			double noise = (NOISE(j,k)/((x2-x1)*(y2-y1)))*(x2-x)*(y2-y) + \
				     (NOISE(j,k+1)/((x2-x1)*(y2-y1)))*(x-x1)*(y2-y) + \
				     (NOISE(j+1,k)/((x2-x1)*(y2-y1)))*(x2-x)*(y-y1) + \
				   (NOISE(j+1,k+1)/((x2-x1)*(y2-y1)))*(x-x1)*(y-y1);

			temp += (noise);
		}

		map->snow[y][x] = (temp/num) * 5.0;
		if(map->snow[y][x] > 3)
			map->snow[y][x] = 3;
	}
	}

	/* cleanup */
/*	for(i = initial_size, k=0; k<num; k++, i*2) {

		for(x=0; x<i; x++)
			free(noise_funcs[k][x]);

		free(noise_funcs[k]);
	} */


	return;


/*
	int i, k;

	for(i=0; i<map->height; i++)
	for(k=0; k<map->width; k++)
		map->snow[i][k] = 3;
//		map->snow[i][k] = range(0, 4);

	return;
*/
}

void trees(level map)
{
	int i, k;

	for(i=0; i<map->height; i++)
	for(k=0; k<map->width; k++)
		map->trees[i][k] = (range(0,20)==1);

	return;
}
