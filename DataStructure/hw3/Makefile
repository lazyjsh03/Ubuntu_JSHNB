CC = gcc
CFLAGS = -Wall -g -O

# 실행 파일 이름
TARGET = wordCount

# 컴파일할 C 파일 목록
SRCS = wordCount.c bst.c qsort.c

# 생성될 오브젝트 파일 목록
OBJS = $(SRCS:.c=.o)

# 기본 빌드 규칙
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# 오브젝트 파일 생성 규칙
wordCount.o: wordCount.c bst.h qsort.h
	$(CC) $(CFLAGS) -c wordCount.c

bst.o: bst.c bst.h
	$(CC) $(CFLAGS) -c bst.c

qsort.o: qsort.c qsort.h
	$(CC) $(CFLAGS) -c qsort.c

# clean
clean:
	rm -f $(TARGET) $(OBJS) core