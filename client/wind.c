#include <ncurses.h>

#include "wind.h"
#include "rack.h"

WINDOW *initboard()
{
    WINDOW *temp;

    int height = 16;
    int width = 3 * 16;
    int starty = 0;
    int startx = 0;

    temp = newwin(height, width, starty, startx);

    wrefresh(temp);

    return temp;
}

WINDOW *inputwin()
{
    WINDOW *temp;

    int height = 1;
    int width = COLS;
    int starty = (LINES - height);
    int startx = (COLS - width);

    temp = newwin(height, width, starty, startx);
    scrollok(temp, TRUE);
    wsetscrreg(temp, 0, 0);
    keypad(temp, TRUE);
    waddstr(temp, "Chat: ");

    wrefresh(temp);

    return temp;
}

WINDOW *chatwin()
{
    WINDOW *temp;

    int height = 5;
    int width = COLS;
    int starty = (LINES - height - 1);
    int startx = (COLS - width);

    temp = newwin(height, width, starty, startx);
    box(temp, 0, 0);
    scrollok(temp, TRUE);
    wsetscrreg(temp, 1, height);
    waddstr(temp, "Chat: ");
    wmove(temp, 1, 1);

    wrefresh(temp);

    return temp;
}

WINDOW *rackwin()
{
    WINDOW *temp;

    int height = 1;
    int width = 9;
    //int starty = (LINES - 6 - 2);
    //int startx = (3 * 16) + 1;
    int starty = LINES - 7;
    int startx = (COLS - 4) / 2;

    temp = newwin(height, width, starty, startx);
    //rackbrackets(RACKSIZE);
    //displayletters(RACKSIZE, rackletters);
    
    wrefresh(temp);

    return temp;
}

WINDOW *helpwin()
{
    WINDOW *temp;

    int height = 10;
    int width = 25;
    int starty = 0;
    int startx = (COLS - width);

    temp = newwin(height, width, starty, startx);
    box(temp, 0, 0);
    scrollok(temp, TRUE);
    wsetscrreg(temp, 1, height);
    wmove(temp, 1, 1);

    wwrite(temp, "T = triple word score");
    wwrite(temp, "t = triple letter score");
    wwrite(temp, "D = double word score");
    wwrite(temp, "d = double letter score");
    wwrite(temp, "* = center of the board");

    wrefresh(temp);

    return temp;
}

void wwrite(WINDOW *win, char *str)
{
    wprintw(win,"%s", str);
    wprintw(win, "\n ");
    box(win, 0, 0);
    wrefresh(win);
    //mvwaddstr(win, 0, 0, "Output: ");
}
