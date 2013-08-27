#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

#define BSIZE 15 

char board[BSIZE][BSIZE];

void clearsqarray(int size, char array[size][size]);
void printarr(WINDOW *win, int size, char array[size][size]);
void sprintarr(WINDOW *win, int size, char array[size][size], int x, int y);
void sdprintarr(WINDOW *win, int size, char array[size][size], int x, int y);
void saprintarr(WINDOW *win, int size, char array[size][size], int x, int y);
void chprintarr(WINDOW *win, int x, int y, int ch);
void delchprintarr(WINDOW *win, int x, int y);
void strplc_d(int y, int x, int size, char array[size][size], char *str, int strbytes);
void strplc_a(int x, int y, int size, char array[size][size], char *str, int strbytes);
void strdel_d(int x, int y, int size, char array[size][size], int strbytes);
void strdel_a(int x, int y, int size, char array[size][size], int strbytes);
void printspecial(WINDOW* win, int size);
