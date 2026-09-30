# Compiler and flags
CC = gcc
CFLAGS = -Wall -I./include -g

# Sources and objects
SRCS = src/main.c src/board.c src/game.c
OBJS = $(SRCS:.c=.o)

# Target executable
TARGET = twixt


all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Compile rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)