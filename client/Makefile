CC = cc
LD = cc
RM = /bin/rm -f
CFLAGS = -Wall -O2
LDFLAGS = -lncurses

SRC_C = client.c input.c wind.c board.c output.c rack.c util.c place.c
OBJ_C = $(SRC_C:.c=.o)

PROG_C = client

all: $(PROG_C)

$(PROG_C): $(OBJ_C)
	$(LD) $(LDFLAGS) $(OBJ_C) -o $(PROG_C)
	$(RM) $(OBJ_C)

$(OBJ_C): $(SRC_C)
	$(CC) $(CFLAGS) -c $(SRC_C)

clean:
	$(RM) $(OBJ_C) $(PROG_C)
