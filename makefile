# Variables
CC = gcc
CFLAGS = -Wall -g
SRCS = $(wildcard *.c)
TARGET = pathfinding

# Règle par défaut
all: 
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
	
re: clean all