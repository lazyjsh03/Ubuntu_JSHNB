TARGET=mymath
OBJS=ex12-2-main.o add.o sub.o

CC=gcc
CFLAGS=
OBJS=ex12-2-main.o add.o sub.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

ex12-2-main.o: ex12-2-main.c
	$(CC) $(CFLAGS) -c ex12-2-main.c
add.o: add.c
	$(CC) $(CFLAGS) -c add.c
sub.o: sub.c
	$(CC) $(CFLAGS) -c sub.c

clean:
	rm -f $(OBJS) mymath core
