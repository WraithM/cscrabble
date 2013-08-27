#define RACKSIZE 7

int sublbag(int *bag, char letter);
void fixbag(char *bufrack, int *bag);
void randomrack(char *bufrack, int *bag, int size);
void sendboard(int sock, char *bufout, char *board, int size);
