#include "place.h"

void placeword()
{
    int x, y, ch, i;
    char direction = 'a';
    char buffer[MAXDATASIZE];
    char word[WORDSIZE + 1];

    memset(word, '\0', sizeof(word));

    //Highlight the (0, 0) on the board and the brackets
    x = 0;
    y = 0;
    sprintarr(boardwin, BSIZE, board, x, y);

    //Keyboard arrows and hjkl for controlling the highlighting, loop for when hit enter, that enters the location
    while((ch = wgetch(boardwin)) != 0x0A)
    {
        switch(ch)
        {
            case 'j':
            case KEY_DOWN:
                if(x >= 0 && x <= BSIZE)
                {
                    x--;
                }
                else
                {
                    x = 0;
                }

                sprintarr(boardwin, BSIZE, board, x, y);
                break;
            case 'k':
            case KEY_UP:
                if(x >= 0 && x <= BSIZE)
                {
                    x++;
                }
                else
                {
                    x = 0;
                }

                sprintarr(boardwin, BSIZE, board, x, y);
                break;
            case 'l':
            case KEY_RIGHT:
                if(y >= 0 && y <= BSIZE)
                {
                    y++;
                }
                else
                {
                    y = 0;
                }

                sprintarr(boardwin, BSIZE, board, x, y);
                break;
            case 'h':
            case KEY_LEFT:
                if(y >= 0 && y <= BSIZE)
                {
                    y--;
                }
                else
                {
                    y = 0;
                }

                sprintarr(boardwin, BSIZE, board, x, y);
                break;
        }
    }

    //Up arrow or down arrow to decide direction, and change highlighting, then enter for choice
    while((ch = wgetch(boardwin)) != 0x0A)
    {
        switch(ch)
        {
            case 'j':
            case KEY_UP:
                saprintarr(boardwin, BSIZE, board, x, y);
                direction = 'a';
                break;
            case 'k':
            case KEY_DOWN:
                sdprintarr(boardwin, BSIZE, board, x, y);
                direction = 'd';
                break;
        }
    }

    //Enter word by pressing a letter, check if in rack, move to next space in direction, then enter to send
    i = 0;

    while((ch = wgetch(input)) != 0x0A && i <= WORDSIZE)
    {
        switch(ch)
        {
            case KEY_BACKSPACE:
            case 0x7F:
            case 0x08:
                if(i >= 0)
                {
                    i--;
                    word[i] = '\0';
                    if(direction == 'a')
                        delchprintarr(boardwin, x, y + i);
                    else
                        delchprintarr(boardwin, x + i, y);
                }
                break;
            default:
                if(isprint(ch) != 0)
                {
                    ch = toupper(ch);

                    if(findletter(ch, WORDSIZE, rackletters)) 
                    {
                        word[i] = ch;

                        if(direction == 'a')
                            chprintarr(boardwin, x, y + i, ch);
                        else
                            chprintarr(boardwin, x + i, y, ch);
                    }
                    else
                    {
                        wwrite(output, "**NO LETTER ON RACK**");
                        break;
                    }

                    i++;
                }
        }
    }

    if(word[0] == '\0')
        return;

    word[i] = '\0';

    //Send
    if(x > 10)
    {
        if(y > 10)
            sprintf(buffer, "p%c%i%i%s", direction,  y, x, word);
        else
            sprintf(buffer, "p%c0%i%i%s", direction, y, x, word); 
    }
    else
    {
        if(y > 10)
            sprintf(buffer, "p%c%i0%i%s", direction, y, x, word);
        else
            sprintf(buffer, "p%c0%i0%i%s", direction, y, x, word);
    }

    send(sock, buffer, strlen(buffer), 0);

    displayletters(WORDSIZE, rackletters);
    printarr(boardwin, BSIZE, board);

    //go back to chat
    wrefresh(input);
}
