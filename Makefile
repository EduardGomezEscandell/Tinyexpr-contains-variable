CC = gcc
CCFLAGS = -Wall -Wall -Wshadow -g
LFLAGS = -g -lm

all:
	$(CC) $(CCFLAGS) tree_explore.c tinyexpr/tinyexpr.c -o tree_explore.out $(LFLAGS)