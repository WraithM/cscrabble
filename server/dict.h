#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DICT "dict"
#define MAXDICTSIZE 87955
#define MAXWORDSIZE 17 

char *dictlen[MAXWORDSIZE];

char **opendict(char *filename);
int searchdict(char *word);
