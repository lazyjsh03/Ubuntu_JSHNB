SRCS = $(shell ls *.c)
TARGETS = $(SRCS:%.c=%)

CC = gcc
CFLAGS = -D LINUX

.SUFFIXES : .o .c
%.o : %.c
	$(CC) -g $(CFLAGS) -o $@ $<

all : $(TARGETS)

clean:
	rm -rf *.o $(TARGETS)
