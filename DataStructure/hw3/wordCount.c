#include <stdio.h>
#include <string.h>
#include "bst.h"   // BST 관련 함수 및 구조체 정의
#include "qsort.h" // qsort 관련 함수 정의

#define INPUT_FILE "tom-word-list.txt"
#define DISPLAY_COUNT 10    // 상/하위 출력 개수

TNode* root = NULL;
long long totalWordCount = 0;   // 총 단어 수
long long wordCount = 0;    // 고유 단어 수

// 파일 읽기 및 BST 구축 함수
void readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        char errorMsg[256];
        snprintf(errorMsg, sizeof(errorMsg), "파일 열기 오류: %s", filename);
        perror(errorMsg);
        exit(EXIT_FAILURE);
    }

    char line_buffer[MAX_WORD_LEN + 2]; // 단어, 개행, 널 문자

    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
        // 개행 문자 제거
        line_buffer[strcspn(line_buffer, "\n")] = 0;

        if (strlen(line_buffer) > 0) { // 비어있지 않은 줄만 처리
            totalWordCount++; // 파일에서 읽은 모든 단어(중복 포함) 카운트

            WordFreq item; // BST에 삽입, 빈도수 업데이트할 아이템
            strncpy(item.word, line_buffer, MAX_WORD_LEN - 1);
            item.word[MAX_WORD_LEN - 1] = '\0'; // 널 종료 보장
            
            // search_bst를 사용하여 이미 단어가 있는지 확인
            WordFreq* exist_data = search_bst(root, item.word);

            if (exist_data != NULL) {
                // 단어가 이미 존재하면 빈도수만 증가
                exist_data->freq++;
            } else {
                // 새로운 단어면 빈도수를 1로 설정하여 BST에 삽입
                item.freq = 1;
                root = insert_bst(root, item);
            }
        }
    }
    fclose(file);

    wordCount = count_bst_nodes(root);
}

// --- P1 출력 함수 ---
void printP1() {
    printf("[P1] 입력 단어 내역:\n");
    printf("입력 단어 총 개수= %lld, 고유 단어 총 개수= %lld\n", totalWordCount, wordCount);
}

// --- P2 출력 함수 ---
void printP2(WordFreq sorted_words[], int count, const char* keyWord) {
    printf("\n[P2] 탐색지정 단어와 출현빈도:\n");
    printf("오름차순 정렬된 단어 기준 상하위 10개 단어와 출현빈도:\n");

    int limit_top = (count < DISPLAY_COUNT) ? count : DISPLAY_COUNT;    // 상위 경계 결정
    for (int i = 0; i < limit_top; i++) {   // 상위 목록 출력
        printf("('%s', %d)\n", sorted_words[i].word, sorted_words[i].freq);
    }

    if (count > DISPLAY_COUNT) {    // 고유 단어 개수가 10보다 클 때
        if (count > DISPLAY_COUNT * 2) {    // 고유 단어 개수가 20보다 클 때(가려지는 부분이 있음)
             printf(".............\n");
        }
        
        // 하위 목록 출력
        // count가 11~20개 사이일 경우: 상위 10개 출력 후 나머지 (count - DISPLAY_COUNT)개 출력
        // count가 20개 초과일 경우: 하위 DISPLAY_COUNT (10)개 출력
        int start;  // 시작 index
        int items;  // 출력 개수

        if (count > DISPLAY_COUNT * 2) {    // 21개 이상 -> 하위 10개
            start = count - DISPLAY_COUNT;
            items = DISPLAY_COUNT;
        } else {                            // 11개 ~ 20개 -> 상위 10개 다음부터 끝까지
            start = DISPLAY_COUNT; 
            items = count - DISPLAY_COUNT;
        }
        
        for (int i = 0; i < items; i++) {
             if (start + i < count) {
                printf("('%s', %d)\n", sorted_words[start + i].word, sorted_words[start + i].freq);
            }
        }
    }

    // --- 특정 단어 검색 및 빈도수 출력 ---
    WordFreq* found_word = search_bst(root, keyWord);
    if (found_word != NULL) {
        printf("\n탐색지정 단어('%s', %d)\n", keyWord, found_word->freq);
    } else {
        printf("\n탐색지정단어(%s) 없음\n", keyWord);
    }
}

// --- P3 출력 함수 ---
void printP3(WordFreq sorted_words[], int count, int keyFreq) {     // 빈도수 정렬된 배열 전달
    printf("\n[P3] 탐색지정빈도와 단어:\n");
    printf("출현 빈도 기준 내림차순 정렬된 상하위 10개 출현빈도와 단어:\n");

    // 상/하위 목록 출력
    int limit_top = (count < DISPLAY_COUNT) ? count : DISPLAY_COUNT;
    for (int i = 0; i < limit_top; i++) {
        printf("(%d, '%s')\n", sorted_words[i].freq, sorted_words[i].word);
    }

    if (count > DISPLAY_COUNT) {
        if (count > DISPLAY_COUNT * 2) {
             printf(".............\n");
        }
        
        int start;
        int items;

        if (count > DISPLAY_COUNT * 2) { 
            start = count - DISPLAY_COUNT;
            items = DISPLAY_COUNT;
        } else { 
            start = DISPLAY_COUNT; 
            items = count - DISPLAY_COUNT;
        }
        
        for (int i = 0; i < items; i++) {
            if (start + i < count) {
                 printf("(%d, '%s')\n", sorted_words[start + i].freq, sorted_words[start + i].word);
            }
        }
    }

    // 특정 빈도수 단어 검색 및 출력
    // 단어가 20개가 넘어갈 경우 상/하위로 나눠서 출력
    printf("\n탐색지정빈도(%d)\n\n", keyFreq);
    
    // 특정 빈도수를 가진 단어들만 저장할 임시 배열
    WordFreq* found_words = (WordFreq*)malloc(count * sizeof(WordFreq)); // 최대 count 개수만큼 할당
    if (found_words == NULL && count > 0) { // count가 0이면 malloc 안 해도 됨
        perror("found_freq_words 메모리 할당 실패 (printP3)");
        // 오류 처리
        if (count == 0) printf(" 해당 단어 없음\n");
        return;
    }
    int found_count = 0;    // 찾은 단어 개수

    // 전체 배열에서 지정된 빈도수를 가진 단어들을 찾아서 임시 배열에 복사
    for (int i = 0; i < count; i++) {
        if (sorted_words[i].freq == keyFreq) {
            found_words[found_count++] = sorted_words[i];
        } else if (sorted_words[i].freq < keyFreq) {
            // 이미 빈도수 내림차순 정렬이므로, 더 작은 빈도수를 만나면 종료
            break;
        }
    }

    if (found_count == 0) {
        printf(" 해당 단어 없음\n");
    } else {
        // found_words 배열 -> 단어 오름차순으로 정렬된 상태
        
        if (found_count <= DISPLAY_COUNT * 2) { // 20개 이하이면 모두 출력
            for (int i = 0; i < found_count; i++) {
                printf("(%d, '%s')\n", found_words[i].freq, found_words[i].word);
            }
        } else { // 20개 초과이면 상위 10개, "...", 하위 10개 출력
            // 상위 10개 출력
            for (int i = 0; i < DISPLAY_COUNT; i++) {
                printf("(%d, '%s')\n", found_words[i].freq, found_words[i].word);
            }
            printf(".............\n");
            // 하위 10개 출력
            for (int i = found_count - DISPLAY_COUNT; i < found_count; i++) {
                printf("(%d, '%s')\n", found_words[i].freq, found_words[i].word);
            }
        }
    }

    if (found_words != NULL) { // count가 0일 때 malloc이 호출되지 않았을 수 있으므로 확인
        free(found_words);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) { 
        fprintf(stderr, "사용법: %s <탐색지정단어> <탐색지정빈도>\n", argv[0]);
        return 1;
    }
    const char* keyWord = argv[1];
    int keyFreq = atoi(argv[2]);    // 명령행 인자로 전달받은 빈도수를 정수로 변환

    // 명령줄 인자 검사
    if (keyFreq <= 0 && strcmp(argv[2], "0") != 0 && strcmp(argv[2], "-0") != 0) {
        // atoi는 빈 문자열이거나 정수로 변환할 수 없으면 0반환('', 'abc')
        // 사용자가 실재로 0을 입력한 것이 아니면 오류로 간주
        printf("탐색지정빈도('%s') 입력 오류\n", argv[2]);
        return 2;   // 프로그램 종료 코드
    }
    if (keyFreq == 0){
        printf("탐색지정빈도는 0이 될 수 없습니다.\n");
        return 2;
    }

    // 파일 읽고 BST 구축
    readFile(INPUT_FILE);

    // P1 출력
    printP1();

    // P2, P3 출력
    if (wordCount > 0) {   
        // 고유 단어가 하나 이상일 때
        WordFreq* sortedArray = (WordFreq*)malloc(wordCount * sizeof(WordFreq));   // sortedArray 메모리 할당
        if (sortedArray == NULL) {  // sortedArray 메모리 할당 실패 시 오류 반환
            perror("sortedArray 메모리 할당 실패");
            delete_tree(root);
            return EXIT_FAILURE;
        }
        
        // 중위 순회를 통해 알파벳 정렬
        inorder_bst(root, sortedArray, 0);

        // P2 출력
        printP2(sortedArray, wordCount, keyWord);

        // 퀵 정렬을 사용해 sortedArray를 빈도수 기준으로 정렬
        quickSort(sortedArray, 0, wordCount - 1);

        // P3 출력
        printP3(sortedArray, wordCount, keyFreq);

        free(sortedArray);  // sortedArray 메모리 해제
    } else {
        // 고유 단어가 없는 경우 P2 처리
        printf("\n[P2] 탐색지정 단어와 출현빈도:\n");
        printf("오름차순 정렬된 단어 기준 상하위 10개 단어와 출현빈도:\n");
        // 상/하위 목록 내용 없음
        printf("\n탐색지정단어(%s) 없음\n", keyWord); 
        // 특정 단어 검색 결과도 없음

        // 고유 단어가 없는 경우 P3 처리
        printf("\n[P3] 탐색지정빈도와 단어:\n");
        printf("출현 빈도 기준 내림차순 정렬된 상하위 10개 출현빈도와 단어:\n");
        printf("\n탐색지정빈도(%d)\n\n", keyFreq);
        printf(" 해당 단어 없음\n");
    }

    // 메모리 해제, 루트 노드 초기화
    delete_tree(root);
    root = NULL;

    return 0;
}