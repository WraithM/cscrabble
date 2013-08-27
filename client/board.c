#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

#include "board.h"

void clearsqarray(int size, char array[size][size])
{
    int i, j;

    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            array[i][j] = 0x20;
        }
    }
}

void printarr(WINDOW *win, int size, char array[size][size])
{
    int i, j;

    werase(win);
    wmove(win, 0, 0);

    //Formatting
    wprintw(win, "   ");
    for(i = 0; i < size; i++)
        if(i < 10)
            wprintw(win, " %d ", i);
        else
            wprintw(win, "%d ", i);

    //End of formatting

    for(i = 0; i < size; i++)
    {
        wprintw(win, "%d", i); //Formatting

        for(j = 0; j < size; j++)
        {
            mvwprintw(win, i + 1, (j * 3) + 3, "[%c]", array[i][j]);
        }
    }

    wrefresh(win);
}

void sprintarr(WINDOW *win, int size, char array[size][size], int x, int y)
{
    int i, j;

    werase(win);
    wmove(win, 0, 0);

    //Formatting
    wprintw(win, "   ");
    for(i = 0; i < size; i++)
        if(i < 10)
            wprintw(win, " %d ", i);
        else
            wprintw(win, "%d ", i);

    //End of formatting

    for(i = 0; i < size; i++)
    {
        wprintw(win, "%d", i); //Formatting

        for(j = 0; j < size; j++)
        {
            if(i == x && j == y)
                wattron(win, A_BOLD);
            else
                wattroff(win, A_BOLD);

            mvwprintw(win, i + 1, (j * 3) + 3, "[%c]", array[i][j]);
        }
    }

    wrefresh(win);
}

void sdprintarr(WINDOW *win, int size, char array[size][size], int x, int y)
{
    int i, j;

    werase(win);
    wmove(win, 0, 0);

    //Formatting
    wprintw(win, "   ");
    for(i = 0; i < size; i++)
        if(i < 10)
            wprintw(win, " %d ", i);
        else
            wprintw(win, "%d ", i);

    //End of formatting

    for(i = 0; i < size; i++)
    {
        wprintw(win, "%d", i); //Formatting

        for(j = 0; j < size; j++)
        {
            if((i == x || i == x + 1) && j == y)
                wattron(win, A_BOLD);
            else
                wattroff(win, A_BOLD);

            mvwprintw(win, i + 1, (j * 3) + 3, "[%c]", array[i][j]);
        }
    }

    wrefresh(win);
}

void saprintarr(WINDOW *win, int size, char array[size][size], int x, int y)
{
    int i, j;

    werase(win);
    wmove(win, 0, 0);

    //Formatting
    wprintw(win, "   ");
    for(i = 0; i < size; i++)
        if(i < 10)
            wprintw(win, " %d ", i);
        else
            wprintw(win, "%d ", i);

    //End of formatting

    for(i = 0; i < size; i++)
    {
        wprintw(win, "%d", i); //Formatting

        for(j = 0; j < size; j++)
        {
            if(i == x && (j == y || j == y + 1))
                wattron(win, A_BOLD);
            else
                wattroff(win, A_BOLD);

            mvwprintw(win, i + 1, (j * 3) + 3, "[%c]", array[i][j]);
        }
    }

    wrefresh(win);
}

void chprintarr(WINDOW *win, int x, int y, int ch)
{
    mvwprintw(win, x + 1, (y * 3) + 3, "[%c]", ch);
    wrefresh(win);
}

void delchprintarr(WINDOW *win, int x, int y)
{
    mvwprintw(win, x + 1, (y * 3) + 3, "[ ]");
    wrefresh(win);
}
void strplc_d(int y, int x, int size, char array[size][size], char *str, int strbytes)
{
    int i;

    if((x + strbytes) < size)
        for(i = x; i <= (x + strbytes - 1); i++)
            array[i][y] = str[i - x];
    else
    {
        printw("error: placement\n");
        beep();
    }
}

void strplc_a(int x, int y, int size, char array[size][size], char *str, int strbytes)
{
    if((y + strbytes) < size)
        strncpy(array[y] + x, str, strbytes);
    else
    {
        printw("error: placement\n");
        beep();
    }
}

void strdel_d(int x, int y, int size, char array[size][size], int strbytes)
{
    int i;

    if((x + strbytes) < size)
        for(i = x; i <= (x + strbytes - 1); i++)
            array[i][y] = ' ';
    else
    {
        printw("error: deletion\n");
        beep();
    }
}

void strdel_a(int x, int y, int size, char array[size][size], int strbytes)
{
    if((y + strbytes) < size)
        memset(array[y] + x, ' ', strbytes);
    else
    {
        printw("error: deletion\n");
        beep();
    }
}

void printspecial(WINDOW *win, int size)
{
    /*
    T = triple word score
    t = triple letter score
    D = double word score
    d = double letter score
    * = center of the board
    */

    //Perhaps checking what's in the board, then printing these out if there's nothing there would help.

    int i;

    chprintarr(win, (size - 1)/2, (size - 1)/2, '*');

    for(i = 1; i <= 4; i++)
    {
        chprintarr(win, i, i, 'd');
        chprintarr(win, i, size - 1 - i, 'd');
        chprintarr(win, size - 1 - i, i, 'd');
        chprintarr(win, size - 1 - i, size - 1 - i, 'd');
    }

    for(i = 0; i < size; i += 7)
    {
        chprintarr(win, i, 0, 'T');
        chprintarr(win, 0, i, 'T');
        chprintarr(win, i, size - 1, 'T');
        chprintarr(win, size - 1, i, 'T');
    }

    wrefresh(win);
}
