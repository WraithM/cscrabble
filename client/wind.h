#include <ncurses.h>

WINDOW *input, *output, *boardwin, *rack, *help;

WINDOW *initboard();
WINDOW *inputwin();
WINDOW *chatwin();
WINDOW *rackwin();
WINDOW *helpwin();
void wwrite(WINDOW *win, char *str);
