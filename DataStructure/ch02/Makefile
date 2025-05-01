SRCS1 = array_1D.c complex.c matrix_sparse.c array_func.c matrix.c polynomial.c
SRCS2 = sparse_poly.c
SRCS3 = string_test.c

TARGET1 = array_1D complex matrix_sparse array_func matrix polynomial 
TARGET2 = sparse_poly
TARGET3 = string_test

CC = gcc
CFLAGS = -D LINUX

all : $(TARGET1) $(TARGET2) $(TARGET3)

$(TARGET2) : sparse_poly.c
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(TARGET3) : string_test.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o $(TARGET1) $(TARGET2) $(TARGET3)
