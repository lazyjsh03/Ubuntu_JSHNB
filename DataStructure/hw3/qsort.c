#include "qsort.h"
#include <string.h>  // strcmp

// 두 WordFreq 객체를 교환하는 함수
static void swap(WordFreq* a, WordFreq* b) {
    WordFreq temp = *a;
    *a = *b;
    *b = temp;
}

// 비교 함수: 빈도수 내림차순, 빈도수가 같을 시 단어 오름차순
static int compare(const WordFreq* a, const WordFreq* b) {
    if (a->freq != b->freq) {
        return b->freq - a->freq; // 빈도수 내림차순: b의 빈도가 크면 a가 먼저 오므로 (b-a > 0) -> a가 뒤로감
                                  // 따라서 a의 빈도가 크면 음수가 되어 a가 앞으로 오도록 설정
    }
    // 빈도수가 같으면 단어 오름차순
    return strcmp(a->word, b->word);
}

// 파티션 함수: 피벗을 배열의 첫 번째 요소로 선택
static int partition(WordFreq arr[], int left, int right) {
    WordFreq pivot = arr[left]; // 첫 번째 요소를 피벗으로 선택
    int low = left + 1;  
    int high = right;   

    while (low <= high) {
        while (low <= high && compare(&arr[low], &pivot) <= 0) {
            low++;
        }
        while (low <= high && compare(&arr[high], &pivot) > 0) {
            high--;
        }
        if (low < high) {
            swap(&arr[low], &arr[high]);
        }
    }

    if (high > left) { 
        swap(&arr[left], &arr[high]);
    }
    
    return high; // 피벗의 최종 위치 반환
}

// 퀵 정렬 함수
void quickSort(WordFreq arr[], int left, int right) {
    if (left < right) {
        if (arr == NULL || left < 0 || right < 0 ) {
            // 입력 유효성 검사
            return;
        }
        // 피벗의 최종 위치를 얻음
        int pi = partition(arr, left, right);

        // 피벗을 기준으로 좌우 부분 배열을 각각 정렬
        quickSort(arr, left, pi - 1);  // 피벗 왼쪽 부분 정렬
        quickSort(arr, pi + 1, right); // 피벗 오른쪽 부분 정렬
    }
}