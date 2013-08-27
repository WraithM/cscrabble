#include "dict.h"

char **opendict(char *filename)
{
    int i;
    FILE *dictfile;

    char **dictarray = malloc(MAXDICTSIZE * sizeof(char *));
    dictarray[0] = malloc(MAXDICTSIZE * MAXWORDSIZE);
    for(i = 1; i < MAXDICTSIZE; i++)
        dictarray[i] = dictarray[0] + i * MAXWORDSIZE;

    dictfile = fopen(filename, "r");

    i = 0;

    while(i < MAXDICTSIZE && fscanf(dictfile, "%s", dictarray[i]))
    {
        if(dictarray[i][strlen(dictarray[i]) - 1] == '\n')
            dictarray[i][strlen(dictarray[i]) - 1] = '\0';
        
        i++;
    }

    dictlen[strlen(dictarray[0])] = dictarray[0];

    for(i = 1; i < MAXDICTSIZE; i++)
    {
        if(strlen(dictarray[i]) > strlen(dictarray[i - 1]))
        {
            dictlen[strlen(dictarray[i])] = dictarray[i];
        }
    }

    fclose(dictfile);

    return dictarray;
}

int searchdict(char *word)
{
    char *ptr = 0;

    if(strlen(word) < 2)
        return 0;

    ptr = (char *) bsearch(word, dictlen[strlen(word)], (dictlen[strlen(word) + 1] - dictlen[strlen(word)])/MAXWORDSIZE, MAXWORDSIZE, (int(*)(const void *, const void *)) strcmp);

    if(ptr != NULL)
        return 1;
    else
        return 0;
}
