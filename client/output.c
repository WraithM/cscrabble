#include <sys/types.h>
#include <sys/socket.h>

#include "client.h"
#include "place.h"

void handleout(char *buffer, int size)
{
    char bufout[MAXDATASIZE];

    if(strcmp(buffer, "q") == 0)
    {
        send(sock, "q", 1, 0);
        return;
    }

    switch(buffer[0])
    {
        case '/':
            switch(buffer[1])
            {
                case 'r':
                    if(strncmp(buffer, "/raw", 4) == 0)
                    {
                        strncpy(bufout, buffer + 5, sizeof(bufout) - 1);
                        bufout[sizeof(bufout) - 1] = '\0';
                        send(sock, bufout, strlen(bufout), 0);
                    }
                    break;
                case 'h':
                    if(strncmp(buffer, "/help", 5) == 0)
                    {
                        if(strncmp(buffer, "/help raw", 9) == 0)
                            wwrite(output, "**Help: /raw <data to send>");
                        else
                            wwrite(output, "**Help: /help <command>**\n **The commands are: raw, q**");
                    }
                    break;
                case 'q':
                    quit();
                    break;
                default:
                    wwrite(output, "**Usage: /<command>**");
            }
            break;
        default:
            bufout[0] = 'c';
            strncpy(bufout + 1, buffer, sizeof(bufout) - 1);
            bufout[sizeof(bufout) - 1] = '\0';
            send(sock, bufout, strlen(bufout), 0);
    }
}

void getoutput(char *inputstr)
{
    int x, y, ch;
    int i = 0;
    char buf[MAXDATASIZE];

    while((ch = wgetch(input)) != 0x0A && i <= MAXDATASIZE)
    {
        switch(ch)
        {
            case KEY_BACKSPACE:
            case 0x7F:
            case 0x08:
                getyx(input, y, x);

                if(x > 6 || i > (COLS - 6))
                {
                    i--;
                    buf[i] = '\0';
                    mvwdelch(input, y, x - 1);
                    wrefresh(input);
                }

                break;
            case CTRL('x'):
                quit();
                break;
            case KEY_UP:
                placeword(); 
                break;
            default:
                if(isprint(ch) != 0)
                {
                    buf[i] = ch;
                    i++;
                    waddch(input, ch);
                    wrefresh(input);
                }
        }
    }

    buf[i] = '\0';
    strcpy(inputstr, buf);
}
