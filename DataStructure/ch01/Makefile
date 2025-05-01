SRCS = $(shell ls *.c)
TARGETS = $(SRCS:%.c=%)

CC = gcc

.SUFFIXES : .o .c
%.o : %.c
	$(CC) $< -o $@

all : $(TARGETS)

clean:
	rm -rf *.o $(TARGETS)
