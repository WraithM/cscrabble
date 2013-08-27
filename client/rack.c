#include <ncurses.h>

#include "rack.h"

void rackbrackets(int size)
{
    mvwaddstr(rack, 0, 0, "[");
    mvwaddstr(rack, 0, size + 1, "]");
    wrefresh(rack);
}

void displayletters(int size, char letters[size])
{
    int i;

    rackbrackets(size);

    for(i = 0; i < size; i++)
        if(*(letters + i) == '[')
            mvwaddstr(rack, 0, i + 1, " ");
        else
            mvwaddstr(rack, 0, i + 1, letters + i);
}

int findletter(int ch, int size, char letters[size])
{
    int i;

    for(i = 0; i < size; i++)
        if(*(letters + i) == ch)
            return 1;
    
    return 0;
}

int delrackletter(int ch, int size, char letters[size])
{
    int i;

    for(i = 0; i < size; i++)
    {
        if(*(letters + i) == ch)
        {
            letters[i] = 0x20;

            return 1;
        }
    }

    return 0;
}

void sortrack(int size, char letters[size])
{
    int i, j;

    for(i = 0; i < size; i++)
        if(*(letters + i) == 0x20)
            for(j = i; j < size; j++)
                if(*(letters + j) != 0x20)
                {
                    letters[i] = letters[j];
                    letters[j] = 0x20;
                    break;
                }
}

void replacerack(char *replace, int amount, int size, char letters[size])
{
    int i, j;

    sortrack(size, letters);

    for(i = 0; i < size; i++)
    {
        if(*(letters + i) == 0x20)
        {
            for(j = 0; j <= amount; j++)
                letters[i + j] = replace[j];
                
            break;
        }
    }

    displayletters(size, letters);
    wrefresh(rack);
}
