SRCS = $(shell ls *.c)
TARGETS = $(SRCS:%.c=%)
CFLAGS += -g

.SUFFIXES : .o .c
%.o : %.c
	$(CC) $(CFLAGS) -o  $@ $<

all : $(TARGETS)

clean:
	rm -rf  bugprg  
