#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <fcntl.h>

#include "client.h"
#include "wind.h"
#include "board.h"
#include "rack.h"

void handlein(char *buffer, int size)
{
    int i, j;
    char bufout[MAXDATASIZE];
    char word[RACKSIZE];

    memset(bufout, '\0', sizeof(bufout));
    memset(word, '\0', sizeof(word));

    if(strcmp(buffer, "ACK") == 0)
        return;

    switch(buffer[0])
    {
        case 'c':
            strncpy(bufout, buffer + 1, sizeof(bufout));
            bufout[sizeof(bufout) - 1] = '\0';
            wwrite(output, bufout);
            break;
        case 'b':
            strncpy(bufout, buffer + 1, sizeof(bufout)); 
            strncpy(*board, bufout, sizeof(board));
            printarr(boardwin, BSIZE, board);
            break;
        //d and r are not working. Fix. They just simply do nothing when they are suppoed to do something.
        case 'd':
            for(i = 0; i <= strlen(buffer); i++)
            {
                if(*(buffer + i) == 'r')
                {
                    for(j = 0; j < i - 1; j++)
                    {
                        bufout[j] = buffer[1 + j];
                        word[j] = buffer[i + j + 1];
                    }
                    break;
                }
            }

            for(i = 0; i < strlen(bufout); i++)
                delrackletter(bufout[i], RACKSIZE, rackletters);

            replacerack(word, strlen(word), RACKSIZE, rackletters);
            break; 
        default:
            strcpy(bufout, "DATA Data: ");
            strncat(bufout, buffer, sizeof(bufout) - strlen(bufout) - 1);
            wwrite(output, bufout);
    }
}

void input_ready(int signo)
{
    char buffer[MAXDATASIZE];
    int numbytes;

    numbytes = recv(sock, buffer, sizeof(buffer), 0);
    buffer[numbytes] = '\0';

    if(numbytes > 0 && strcmp(buffer, "q") != 0)
    {
        handlein(buffer, strlen(buffer));
        input = inputwin();
    }
    else
    {
        quit();
    }
}
