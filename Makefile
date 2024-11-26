CC = gcc
CFLAGS = -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result
LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC = bambam.c
EXE = bambam

game:
	$(CC) $(SRC) $(LDLIBS) -o $(EXE)
 
clean:
	rm -v $(EXE)

