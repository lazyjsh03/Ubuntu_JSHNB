#include <stdio.h>
#include <stdlib.h> // atoi, malloc, free, exit 함수 사용
#include <string.h> // strcmp, strncpy, strlen, strcspn 함수 사용

// 직접 만든 헤더 파일 포함
#include "bst.h"   // BST 관련 정의 및 함수 선언 (WordFreq 구조체 정의 포함 가정)
#include "qsort.h" // 퀵 정렬 함수 선언

#define DISPLAY_COUNT 10        // 상위/하위 목록에 표시할 단어 수
#define INPUT_FILE "tom-word-list.txt" // 입력 파일명

// 전역 변수 (또는 main 내 지역 변수로 선언 후 포인터로 전달 가능)
TNode* wordTreeRoot = NULL;     // BST 루트 노드
long long totalWordCount = 0;   // 전체 단어 수 (파일에서 읽은 모든 단어)
int uniqueWordCount = 0;      // 고유 단어 수 (BST 노드 수)

// --- 파일 읽기 함수 ---
void readWordsFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        char errorMsg[256];
        snprintf(errorMsg, sizeof(errorMsg), "파일 열기 오류: %s", filename);
        perror(errorMsg);
        exit(EXIT_FAILURE);
    }

    char line_buffer[MAX_WORD_LEN + 2];

    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
        line_buffer[strcspn(line_buffer, "\n")] = 0;
        line_buffer[strcspn(line_buffer, "\r")] = 0;

        if (strlen(line_buffer) > 0) {
            totalWordCount++;

            WordFreq item;
            strncpy(item.word, line_buffer, MAX_WORD_LEN -1);
            item.word[MAX_WORD_LEN -1] = '\0';
            item.freq = 1;

            // search_word_bst는 WordFreq*를 반환합니다.
            WordFreq* foundData = search_word_bst(wordTreeRoot, item.word);
            if (foundData != NULL) { // 이미 단어가 BST에 있는 경우
                foundData->freq++;   // 해당 단어의 빈도수만 증가
            } else { // 새 단어인 경우
                wordTreeRoot = insert_word_bst(wordTreeRoot, item);
            }
        }
    }
    fclose(file);

    uniqueWordCount = count_bst_nodes(wordTreeRoot);
}

// --- P1: 입력 단어 내역 출력 함수 ---
void printP1_Stats() {
    printf("[P1] 입력 단어 내역:\n");
    printf("입력 단어 총 개수= %lld, 고유 단어 총 개수= %d\n", totalWordCount, uniqueWordCount);
}

// --- P2: 알파벳순 정렬 및 특정 단어 검색 결과 출력 함수 ---
void printP2_AlphaSorted(WordFreq sorted_alpha_words[], int count, const char* search_word_arg) {
    printf("\n[P2] 탐색지정 단어와 출현빈도:\n");
    printf("오름차순 정렬된 단어 기준 상하위 10개 단어와 출현빈도:\n");

    int limit_top = (count < DISPLAY_COUNT) ? count : DISPLAY_COUNT;
    for (int i = 0; i < limit_top; i++) {
        printf("('%s', %d)\n", sorted_alpha_words[i].word, sorted_alpha_words[i].freq);
    }

    if (count > DISPLAY_COUNT) {
        if (count > DISPLAY_COUNT * 2) { // 상위 10개와 하위 10개가 겹치지 않을 만큼 충분히 많을 때
             printf(".............\n");
        }
        
        // 하위 목록 출력 로직 수정
        // count가 11~20개 사이일 경우: 상위 10개 출력 후 나머지 (count - DISPLAY_COUNT)개 출력
        // count가 20개 초과일 경우: 하위 DISPLAY_COUNT (10)개 출력
        int start_index_for_bottom;
        int end_index_for_bottom = count;

        if (count > DISPLAY_COUNT * 2) { // 21개 이상
            start_index_for_bottom = count - DISPLAY_COUNT;
        } else { // 11개 ~ 20개 사이
            start_index_for_bottom = DISPLAY_COUNT; // 상위 10개 다음부터
        }
        
        for (int i = start_index_for_bottom; i < end_index_for_bottom; i++) {
            printf("('%s', %d)\n", sorted_alpha_words[i].word, sorted_alpha_words[i].freq);
        }
    }


    WordFreq* found_word_ptr = search_word_bst(wordTreeRoot, search_word_arg);
    if (found_word_ptr != NULL) {
        printf("\n탐색지정 단어('%s', %d)\n", search_word_arg, found_word_ptr->freq);
    } else {
        printf("\n탐색지정단어(%s) 없음\n", search_word_arg);
    }
}

// --- P3: 빈도수 기준 정렬 및 특정 빈도수 검색 결과 출력 함수 ---
void printP3_FreqSorted(WordFreq freq_sorted_words[], int count, int search_freq_arg) {
    printf("\n[P3] 탐색지정빈도와 단어:\n");
    printf("출현 빈도 기준 내림차순 정렬된 상하위 10개 출현빈도와 단어:\n");

    int limit_top = (count < DISPLAY_COUNT) ? count : DISPLAY_COUNT;
    for (int i = 0; i < limit_top; i++) {
        printf("(%d, '%s')\n", freq_sorted_words[i].freq, freq_sorted_words[i].word);
    }

    if (count > DISPLAY_COUNT) {
        if (count > DISPLAY_COUNT * 2) {
             printf(".............\n");
        }
        
        // 하위 목록 출력 로직 수정 (P2와 동일하게)
        int start_index_for_bottom;
        int end_index_for_bottom = count;

        if (count > DISPLAY_COUNT * 2) { // 21개 이상
            start_index_for_bottom = count - DISPLAY_COUNT;
        } else { // 11개 ~ 20개 사이
            start_index_for_bottom = DISPLAY_COUNT;
        }
        
        for (int i = start_index_for_bottom; i < end_index_for_bottom; i++) {
            printf("(%d, '%s')\n", freq_sorted_words[i].freq, freq_sorted_words[i].word);
        }
    }

    printf("\n탐색지정빈도(%d)\n\n", search_freq_arg);
    int found_for_freq = 0;
    for (int i = 0; i < count; i++) {
        if (freq_sorted_words[i].freq == search_freq_arg) {
            printf("(%d, '%s')\n", freq_sorted_words[i].freq, freq_sorted_words[i].word);
            found_for_freq = 1;
        } else if (freq_sorted_words[i].freq < search_freq_arg && found_for_freq) {
            break;
        } else if (freq_sorted_words[i].freq < search_freq_arg && !found_for_freq) {
            break;
        }
    }
    if (!found_for_freq) {
        printf(" 해당 단어 없음\n");
    }
}

// --- main 함수 ---
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "사용법: %s <탐색지정단어> <탐색지정빈도>\n", argv[0]);
        return 1;
    }

    const char* search_word_arg = argv[1];
    int search_freq_arg = atoi(argv[2]);

    if (search_freq_arg <= 0 && strcmp(argv[2], "0") != 0) {
        printf("탐색지정빈도(%d) 입력 오류\n", search_freq_arg);
        return 2;
    }
     if (search_freq_arg == 0 && strcmp(argv[2], "0") != 0 && strcmp(argv[2], "-0") != 0 ) { // atoi가 변환 실패 시 0 반환
        // 추가: "0"이 아닌 문자열이 atoi로 0이 된 경우 (예: "abc")
        // wordCount.py는 이 경우 ValueError를 내지만, 여기서는 입력 오류로 통일
        printf("탐색지정빈도 값 '%s'는 유효한 숫자가 아닙니다.\n", argv[2]);
        return 2;
    }


    readWordsFromFile(INPUT_FILE);

    printP1_Stats();

    if (uniqueWordCount > 0) {
        WordFreq* word_array = (WordFreq*)malloc(uniqueWordCount * sizeof(WordFreq));
        if (word_array == NULL) {
            perror("word_array 메모리 할당 실패");
            delete_bst_tree(wordTreeRoot);
            return EXIT_FAILURE;
        }

        int current_array_index = 0;
        // inorder_bst_to_array는 업데이트된 인덱스를 반환합니다.
        current_array_index = inorder_bst_to_array(wordTreeRoot, word_array, current_array_index);
        // 또는, inorder_bst_to_array(wordTreeRoot, word_array, 0); 로 호출하고 반환값을 사용하지 않아도
        // uniqueWordCount 만큼 채워질 것으로 예상 (구현에 따라 다름)
        // 여기서는 반환값을 사용하도록 명시적으로 수정.

        printP2_AlphaSorted(word_array, uniqueWordCount, search_word_arg);

        quickSortFreq(word_array, 0, uniqueWordCount - 1); // qsort.c 에 정의된 함수
        printP3_FreqSorted(word_array, uniqueWordCount, search_freq_arg);

        free(word_array);
    } else {
        printf("\n[P2] 탐색지정 단어와 출현빈도:\n");
        printf("오름차순 정렬된 단어 기준 상하위 10개 단어와 출현빈도:\n");
        printf("\n탐색지정단어(%s) 없음\n", search_word_arg);

        printf("\n[P3] 탐색지정빈도와 단어:\n");
        printf("출현 빈도 기준 내림차순 정렬된 상하위 10개 출현빈도와 단어:\n");
        printf("\n탐색지정빈도(%d)\n\n", search_freq_arg);
        printf(" 해당 단어 없음\n");
    }

    delete_bst_tree(wordTreeRoot);

    return 0;
}
