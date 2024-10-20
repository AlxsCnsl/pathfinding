
CC = gcc
CFLAGS = -Wall -g
SRCS = $(wildcard *.c) #pour tout les file.c du projet
TARGET = pathfinding


all: 
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
	
re: clean all