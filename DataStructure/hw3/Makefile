# 컴파일러 및 옵션 설정
CC = gcc
CFLAGS = -Wall -g -O -fcommon  # -Wall: 모든 경고 표시, -g: 디버깅 정보 포함, -O: 최적화, -fcommon: 스크립트 파일에서 사용된 옵션

# 최종 실행 파일 이름
TARGET = wordCount

# 소스 파일 목록 (필요에 따라 추가/수정)
# bst.c와 qsort.c가 wordCount.c에서 사용될 모듈로 가정합니다.
# wordCount.c-script.txt에 언급된 LinkedQueue.o, node2.o 등은
# 현재 BST와 직접 구현한 퀵정렬 방식에서는 명확한 사용처가 보이지 않아 일단 제외합니다.
# 만약 bst.c가 node2.c 등을 내부적으로 사용한다면 해당 .c 파일도 SRCS에 추가하고,
# OBJS에도 해당 .o 파일을 추가해야 합니다.
SRCS = wordCount.c bst.c qsort.c

# 소스 파일로부터 생성될 오브젝트 파일 목록
OBJS = $(SRCS:.c=.o)

# 헤더 파일 목록 (의존성 관리에 사용)
# 각 .c 파일이 의존하는 .h 파일을 명시합니다.
# 예를 들어 wordCount.c가 bst.h와 qsort.h를 include하고,
# bst.c가 bst.h를, qsort.c가 qsort.h와 bst.h를 include하는 경우를 가정합니다.
HDRS = bst.h qsort.h

# 기본 규칙: 최종 실행 파일 생성
# $(TARGET)은 $(OBJS)에 의존합니다.
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# 오브젝트 파일 생성 규칙
# 각 .c 파일은 대응하는 .h 파일 (및 자신이 include하는 다른 헤더)에 의존할 수 있습니다.
# 여기서는 각 .c 파일이 자신의 이름과 같은 .h 파일에 의존한다고 가정하고,
# 추가적인 의존성은 명시적으로 추가합니다.
wordCount.o: wordCount.c bst.h qsort.h
	$(CC) $(CFLAGS) -c wordCount.c

bst.o: bst.c bst.h
	$(CC) $(CFLAGS) -c bst.c

qsort.o: qsort.c qsort.h bst.h # qsort.c가 WordFreq 정의를 위해 bst.h를 포함한다고 가정
	$(CC) $(CFLAGS) -c qsort.c

# clean 규칙: 컴파일된 파일들 삭제
clean:
	rm -f $(TARGET) $(OBJS) core # core 파일도 삭제 대상에 포함

# .PHONY: 가짜 타겟 지정 (실제 파일 이름과 충돌 방지)
.PHONY: clean all

all: $(TARGET)