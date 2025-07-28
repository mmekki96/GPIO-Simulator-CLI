CC = gcc
CFLAG = -c

.PHONY: all

all: main

main: main.o gpio.o cli.o
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAG) $< -o $@

.PHONY: clear

clear: 
	rm -f *.o main
