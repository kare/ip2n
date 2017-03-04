CC = gcc
CFLAGS = -Wall
RM = rm -f

default: all

all: ip2n

ip2n: ip2n.c
	$(CC) $(CFLAGS) -o ip2n ip2n.c

clean:
	$(RM) ip2n

