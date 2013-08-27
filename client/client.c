#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <fcntl.h>
#include <ncurses.h>

#include "client.h"
#include "wind.h"
#include "board.h"
#include "rack.h"

int main(int argc, char *argv[])
{
    int numbytes;
    char playerid[2], buffer[MAXDATASIZE];
    struct sockaddr_in server;
    struct hostent *he;

    if(argc < 2)
    {
        printf("Usage: %s <address>\n", argv[0]);
        exit(1);
    }

    if((he = gethostbyname(argv[1])) == NULL)
    {
        printf("Usage: %s <REAL address>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(server.sin_zero), '\0', sizeof(server.sin_zero));

//Connect and get playerid
    if(connect(sock, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1)
    {
        printf("Error: Could not connect to host.\n");
        exit(1);
    }

    numbytes = recv(sock, playerid, 1, 0);
    playerid[numbytes] = '\0';
    printf("Player ID: %s\n", playerid);

    numbytes = recv(sock, rackletters, sizeof(rackletters), 0);
    rackletters[RACKSIZE] = '\0';

//Asynchronous I/O goes here.
    int flags;

    signal(SIGIO, input_ready);

    fcntl(sock, F_SETOWN, getpid());
    flags = fcntl(STDIN, F_GETFL, 0);
    flags |= O_ASYNC;
    fcntl(sock, F_SETFL, flags);

//Ncurses goes here.
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    refresh();

    help = helpwin();
    rack = rackwin();
    displayletters(RACKSIZE, rackletters);
    boardwin = initboard(); 
    output = chatwin();
    input = inputwin();

//Game stuff goes here.
    clearsqarray(BSIZE, board);
    printarr(boardwin, BSIZE, board);
    printspecial(boardwin, BSIZE);

    while(strcmp(buffer, "q") != 0)
    {
        refresh();
        wrefresh(rack);
        wrefresh(input);
        //wgetnstr(input, buffer, sizeof(buffer));
        getoutput(buffer);
        handleout(buffer, strlen(buffer));
    }

    endwin();
    close(sock);

    printf("\n");

    return 0;
}
