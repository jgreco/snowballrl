#ifndef UTIL_H_
#define UTIL_H_

typedef enum { UP, UPLEFT, LEFT, DOWNLEFT, DOWN, DOWNRIGHT, RIGHT, UPRIGHT } DIRECTION;

#define KUP 'k'
#define KDOWN 'j'
#define KLEFT 'h'
#define KRIGHT 'l'
#define KUPRIGHT 'u'
#define KUPLEFT 'y'
#define KDOWNRIGHT 'n'
#define KDOWNLEFT 'b'

int range(int lower, int upper);

#endif
