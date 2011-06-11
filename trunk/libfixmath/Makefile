CC = gcc
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
BIN = test

LDFLAGS += -lm
CFLAGS  += -O2 -DFIXMATH_NO_CACHE  -W -Wall 

all : $(BIN)

$(BIN) : $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

.c.o :	
	$(CC) $(CFLAGS) $< -c

clean:
	rm -rf *.o *~ $(BIN)

