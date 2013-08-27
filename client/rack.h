#include <string.h>

#include "wind.h"

#define RACKSIZE 7

char rackletters[RACKSIZE + 1];

void rackbrackets(int size);
void displayletters(int size, char letters[size]);
int findletter(int ch, int size, char letters[size]);
int delrackletter(int ch, int size, char letters[size]);
void sortrack(int size, char letters[size]);
void replacerack(char *replace, int amount, int size, char letters[size]);
