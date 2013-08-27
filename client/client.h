#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <fcntl.h>

#include "wind.h"

#ifndef CTRL
#define CTRL(x)     ((x) & 0x1F)
#endif

#define PORT 3000
#define MAXDATASIZE 1024 

#define STDIN 0

int sock;

void handlein(char *buffer, int size);
void input_ready(int signo);
void handleout(char *buffer, int size);
void getoutput(char *inputstr);
void quit();
