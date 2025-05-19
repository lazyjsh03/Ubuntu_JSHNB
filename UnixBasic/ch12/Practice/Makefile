# Makefile

CC=gcc
CFLAGS=-g
OBJS=main.o addnum.o
LIBS=
all:    add

add:    $(OBJS)
	$(CC) $(CFLAGS) -o add $(OBJS) $(LIBS)

main.o:         main.c
	$(CC) $(CFLAGS) -c main.c
addnum.o:       addnum.c
	$(CC) $(CFLAGS) -c addnum.c

clean:
	rm -f $(OBJS) add core
