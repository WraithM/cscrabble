CC = cc
LD = cc
RM = /bin/rm -f
CFLAGS = -Wall -O2 -g
LDFLAGS =

SRC_C = server.c printarrs.c bagrack.c dict.c
OBJ_C = $(SRC_C:.c=.o)

PROG_C = server 

all: $(PROG_C)

$(PROG_C): $(OBJ_C)
	$(LD) $(LDFLAGS) $(OBJ_C) -o $(PROG_C)
	$(RM) $(OBJ_C)

$(OBJ_C): $(SRC_C)
	$(CC) $(CFLAGS) -c $(SRC_C)

clean:
	$(RM) $(OBJ_C) $(PROG_C)
