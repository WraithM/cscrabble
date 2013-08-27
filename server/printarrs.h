#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

#define BSIZE 15 

void clearsqarray(int size, char array[size][size]);
void strplc_d(int y, int x, int size, char array[size][size], char *str, int strbytes);
void strplc_a(int x, int y, int size, char array[size][size], char *str, int strbytes);
void strdel_d(int y, int x, int size, char array[size][size], int strbytes);
void strdel_a(int x, int y, int size, char array[size][size], int strbytes);
