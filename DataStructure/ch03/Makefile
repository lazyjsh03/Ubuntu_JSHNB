SRCS = $(shell ls *.c)
TARGETS = $(SRCS:%.c=%)

CC = gcc 
CFLAGS = -D LINUX

.SUFFIXES : .o .c
%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<

all : $(TARGETS)

clean:
	rm -rf *.o $(TARGETS) 
