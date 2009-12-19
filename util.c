#include "util.h"
#include <stdlib.h>

int range(int lower, int upper)
{
	return lower + rand() % (upper - lower);
}
