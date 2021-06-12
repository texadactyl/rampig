# --- constants
CC=gcc
CFLAGS=-Wall -g -c
LFLAGS=-Wall -g 
BIN=.
OBJECTS=rampig.o

# --- targets
all:	$(BIN)/rampig

$(BIN)/rampig:	$(OBJECTS)
	$(CC) $(LFLAGS) -o $(BIN)/rampig $(OBJECTS)

# --- Store important suffixes in the .SUFFIXES macro
.SUFFIXES:	.o .c	

# --- Generate anyfile.o from anyfile.c
%.o: %.c Makefile
	$(CC) $(CFLAGS) $< 

# --- remove relocatable objects and executable files
clean:
	rm -f $(BIN)/rampig *.o

