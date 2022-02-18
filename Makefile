CC = gcc
BUILD = -O0 -g

TE_CC_FLAGS = -Wall -Wshadow -g
TE_LFLAGS = -lm

CCFLAGS = -Wall -Wextra -Wpedantic -Werror
IFLAGS = -Isrc -Itinyexpr $(TE_LFLAGS)

all:
	$(CC) $(TE_CC_FLAGS) $(BUILD) tinyexpr/tinyexpr.c -c -o tinyexpr/tinyexpr.o $(TE_LFLAGS)
	$(CC) $(CCFLAGS) $(BUILD) src/contains_variable.c -c -o src/contains_variable.o $(IFLAGS)
	$(CC) $(CCFLAGS) $(BUILD) example.c src/contains_variable.o tinyexpr/tinyexpr.o -o sample.out $(IFLAGS)