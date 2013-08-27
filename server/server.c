#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#include "printarrs.h"
#include "bagrack.h"
#include "dict.h"

#define PORT 3000
#define MAXDATASIZE 1024

int main(int argc, char *argv[])
{
    //Game vars
    int playerfd[2];
    char playerid = '1';
    char board[BSIZE][BSIZE];
    char bufrack[8];
    int x, y, num;
    char bufx[3], bufy[3];
    int bag[27] = {9, 2, 2, 4, 12, 2, 3, 2, 9, 1, 1, 4, 2, 6, 8, 2, 1, 6, 4, 6, 4, 2, 2, 1, 2, 1, 2};
    char **dict;
    char word[MAXWORDSIZE];
    char bufout[MAXDATASIZE];

    dict = opendict(DICT);

    srandom(time(NULL));

    clearsqarray(BSIZE, board);

    int listens, newsock, sin_size, bigfd, numbytes, i, j;
    char buffer[MAXDATASIZE];
    struct sockaddr_in localaddr, newaddr, getaddr;
    fd_set master, tempfd;
    int yes = 1;

    listens = socket(PF_INET, SOCK_STREAM, 0);
    setsockopt(listens, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    localaddr.sin_family = AF_INET;
    localaddr.sin_port = htons(PORT);
    localaddr.sin_addr.s_addr = INADDR_ANY;
    memset(&(localaddr.sin_zero), '\0', sizeof(localaddr.sin_zero));

    bind(listens, (struct sockaddr *) &localaddr, sizeof(localaddr));
    listen(listens, 10);

    FD_ZERO(&master);
    FD_ZERO(&tempfd);

    FD_SET(listens, &master);

    bigfd = listens;

    for(;;)
    {
        tempfd = master;

        select(bigfd + 1, &tempfd, NULL, NULL, NULL);

        for(i = 0; i <= bigfd; i++)
        {
            if(FD_ISSET(i, &tempfd))
            {
                if(i == listens)
                {
                    sin_size = sizeof(newaddr);
                    newsock = accept(listens, (struct sockaddr *) &newaddr, &sin_size);
                    
                    FD_SET(newsock, &master);
                    if(newsock > bigfd) 
                        bigfd = newsock;

                    printf("Connection from: %s Socket: %i\n", inet_ntoa(newaddr.sin_addr), newsock);

                    //playerid stuff
                    if(atoi(&playerid) < 2)
                        playerfd[atoi(&playerid) - 1] = newsock;

                    send(newsock, &playerid, sizeof(char), 0);
                    playerid++;

                    //send rack
                    randomrack(bufrack, bag, RACKSIZE);
                    send(newsock, bufrack, strlen(bufrack), 0);
                }
                else
                {
                    if((numbytes = recv(i, buffer, sizeof(buffer), 0)) == 0)
                    {
                        printf("Connection closed: socket %i\n", i);
                        
                        if(playerid == '3' || playerid == '1')
                            playerid = '1';
                        else
                            playerid--;

                        close(i);
                        FD_CLR(i, &master);
                    }
                    else if(numbytes < 0)
                    {
                        perror("recv");
                    }
                    else
                    {
                        //Data handling
                        getpeername(i, (struct sockaddr *) &getaddr, &sin_size);

                        if(buffer[0] != 'c' && buffer [0] != 'r' && buffer[0] != 'p')
                            printf("DATA From: %s Socket: %i Data: %s\n", inet_ntoa(getaddr.sin_addr), i, buffer);

                        send(i, "ACK", 4, 0);

                        if(strcmp(buffer, "q") == 0)
                            exit(0);

                        switch(buffer[0])
                        {
                            case 'c':
                                printf("CHAT From: %s Player: %i Message: %s\n", inet_ntoa(getaddr.sin_addr), i - 3, buffer + 1);

                                for(j = 0; j <= bigfd; j++)
                                    if(FD_ISSET(j, &master))
                                        if(j != listens && j != i)
                                            send(j, buffer, numbytes, 0);
                                break;
                            case 'r':
                                num = atoi(buffer + 1);
                                memset(bufrack, '\0', sizeof(bufrack));
                                randomrack(bufrack, bag, num);

                                sprintf(bufout, "r%s", bufrack);
                                send(i, bufout, strlen(bufout), 0);

                                printf("RACK From: %s Player: %i Number: %i Letters: %s\n", inet_ntoa(getaddr.sin_addr), i - 3, num, bufrack); 
                                break;
                            case 'p':
                                strncpy(bufx, buffer + 2, 2);
                                bufx[2] = '\0';
                                strncpy(bufy, buffer + 4, 2);
                                bufy[2] = '\0';

                                x = atoi(bufx);
                                y = atoi(bufy);

                                strncpy(word, buffer + 6, sizeof(word)); 
                                word[strlen(buffer + 6)] = '\0';

                                printf("PLACE From: %s Player: %i Direction: %c X: %i Y: %i Word: %s\n", inet_ntoa(getaddr.sin_addr), i - 3, buffer[1], x, y, word);

                                if(searchdict(word) != 1)
                                {
                                    send(i, "c*** Word not found ***", 25, 0);
                                    printf("DICT %s not found\n", word);
                                    break;
                                }

                                switch(buffer[1])
                                {
                                    case 'a':
                                        strplc_a(x, y, BSIZE, board, word, strlen(word));
                                        break;
                                    case 'd':
                                        strplc_d(x, y, BSIZE, board, word, strlen(word));
                                        break;
                                }

                                for(j = 0; j <= bigfd; j++)
                                    if(FD_ISSET(j, &master))
                                        if(j != listens)
                                            sendboard(j, buffer, *board, BSIZE);

                                sleep(1);

                                num = strlen(word);
                                memset(bufrack, '\0', sizeof(bufrack));
                                randomrack(bufrack, bag, num);

                                sprintf(bufout, "d%sr%s", word, bufrack);
                                send(i, bufout, strlen(bufout), 0);

                                printf("RACK From: %s Player: %i Number: %i Letters: %s\n", inet_ntoa(getaddr.sin_addr), i - 3, num, bufrack);
                                break;
                        }

                        memset(buffer, '\0', strlen(buffer));
                    }
                }
            }
        }
    }

    return 0;
}
