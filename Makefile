CC = gcc
CFLAGS = -std=c11 -Wall -Werror
RM = rm -rf

default: all

all: build

build: ip2n.c
	$(CC) $(CFLAGS) -o ip2n ip2n.c

clean:
	$(RM) ip2n ip2n.dSYM

install: build
	cp ip2n $(HOME)/bin

debug: ip2n.c
	$(CC) $(CFLAGS) -g -o ip2n ip2n.c

valgrind: clean debug
	valgrind --leak-check=full ./ip2n 127.0.0.1

