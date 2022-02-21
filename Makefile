# Compiler choice
CC = gcc

# Compilation options
RELEASE = -O3
DEBUG= -O0 -g -fsanitize=address -fsanitize=leak -fsanitize=undefined

# Change this line to chose compilation options
BUILD = $(RELEASE)
# BUILD = $(DEBUG)

# Tinyexpr compilation options
TE_CC_FLAGS = -Wall -Wshadow $(BUILD)
TE_LFLAGS = -lm

# Utility compilation options
CCFLAGS = -Wall -Wextra -Wpedantic -Wconversion -Werror $(BUILD)
IFLAGS = -Isrc -Itinyexpr
LFLAGS = $(TE_LFLAGS)

.PHONY = all clean

all: tinyexpr.o contains_variable.o example

tinyexpr.o:
	$(CC) $(TE_CC_FLAGS) $(BUILD) tinyexpr/tinyexpr.c -c -o tinyexpr.o $(TE_LFLAGS)

contains_variable.o:
	$(CC) $(CCFLAGS) $(BUILD) src/contains_variable.c -c -o contains_variable.o $(LFLAGS) $(IFLAGS)

example:
	$(CC) $(CCFLAGS) $(BUILD) example.c contains_variable.o tinyexpr.o -o example $(LFLAGS) $(IFLAGS)

clean:
	rm -f tinyexpr.o contains_variable.o example