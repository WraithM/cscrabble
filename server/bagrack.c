#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "bagrack.h"

#define RACKSIZE 7

int sublbag(int *bag, char letter)
{
    int bufchar;

    bufchar = (int) letter - 65;

    if(bag[bufchar] == 0)
    {
        return -1;
    }
    else
    {
        --bag[bufchar];
        return 1;
    }
}

void fixbag(char *bufrack, int *bag)
{
    int i;
    int bufchar;

    for(i = 0; i < strlen(bufrack); i++)
    {
        bufchar = (int) bufrack[i] - 65;
        ++bag[bufchar];
    }
}

void randomrack(char *bufrack, int *bag, int size)
{
    char letter;
    int i;
    
    for(i = 0; i < size; i++)
    {
        letter = (random() % 27) + 65;

        if(sublbag(bag, letter) == -1)
        {
            fixbag(bufrack, bag);
            randomrack(bufrack, bag, size);
        }

        bufrack[i] = letter;
    }

    bufrack[size] = '\0';

    printf("rack = %s\n", bufrack);
}

void sendboard(int sock, char *bufout, char *board, int size)
{
    int i;

    strcpy(bufout, "b");

    for(i = 0; i <= (size * size); i += size)
        strncat(bufout, board + i, size);

    send(sock, bufout, strlen(bufout), 0);
}
