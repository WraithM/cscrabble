#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

#include "printarrs.h"

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

void strplc_d(int y, int x, int size, char array[size][size], char *str, int strbytes)
{
    int i;

    if((x + strbytes) < size)
        for(i = x; i <= (x + strbytes - 1); i++)
            array[i][y] = str[i - x];
    else
    {
        printf("error: placement\n");
    }
}

void strplc_a(int x, int y, int size, char array[size][size], char *str, int strbytes)
{
    if((y + strbytes) < size)
        strncpy(array[y] + x, str, strbytes);
    else
    {
        printf("error: placement\n");
    }
}

void strdel_d(int y, int x, int size, char array[size][size], int strbytes)
{
    int i;

    if((x + strbytes) < size)
        for(i = x; i <= (x + strbytes - 1); i++)
            array[i][y] = ' ';
    else
    {
        printf("error: deletion\n");
    }
}

void strdel_a(int x, int y, int size, char array[size][size], int strbytes)
{
    if((y + strbytes) < size)
        memset(array[y] + x, ' ', strbytes);
    else
    {
        printf("error: deletion\n");
    }
}
