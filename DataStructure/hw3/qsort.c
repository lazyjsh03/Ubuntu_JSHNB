#include "qsort.h"   // 여기에 WordFreq 정의가 포함된 bst.h가 include 되어 있어야 함
#include <string.h>  // strcmp 사용
#include <stdio.h>   // 디버깅 등에 사용 가능

// 두 WordFreq 객체를 교환하는 내부 함수
static void swap_wordfreq(WordFreq* a, WordFreq* b) {
    WordFreq temp = *a;
    *a = *b;
    *b = temp;
}

// 비교 함수: 빈도수 내림차순, 빈도수 같을 시 단어 오름차순
// a가 b보다 정렬 순서상 앞에 와야 하면 음수 반환
static int compare_wordfreq_for_qsort(const WordFreq* a, const WordFreq* b) {
    if (a->freq != b->freq) {
        return b->freq - a->freq; // 빈도수 내림차순 (b.freq가 크면 a가 먼저, 즉 양수 반환 시 a가 뒤로 감)
                                  // 수정: a.freq가 더 크면 "앞에" 와야 하므로 음수. 즉, b.freq - a.freq
    }
    // 빈도수가 같으면 단어 오름차순
    return strcmp(a->word, b->word);
}

// 파티션 함수 (피벗을 첫 번째 요소 arr[left]로 선택)
// 사용자님이 제공해주신 partition 함수 로직을 기반으로 WordFreq 용으로 수정합니다.
static int partitionFreq(WordFreq arr[], int left, int right) {
    WordFreq pivot = arr[left]; // 피벗을 첫 번째 요소로 선택
    int low = left + 1;
    int high = right;

    while (low <= high) {
        // low는 pivot보다 "큰" (정렬 기준상 뒤에 오는) 첫 번째 요소를 찾을 때까지 증가
        // compare_wordfreq_for_qsort(&arr[low], &pivot) <= 0  --> arr[low]가 pivot보다 작거나 같으면 계속 진행
        while (low <= high && compare_wordfreq_for_qsort(&arr[low], &pivot) <= 0) {
            low++;
        }

        // high는 pivot보다 "작거나 같은" (정렬 기준상 앞에 오는) 첫 번째 요소를 찾을 때까지 감소
        // compare_wordfreq_for_qsort(&arr[high], &pivot) > 0 --> arr[high]가 pivot보다 크면 계속 진행
        while (low <= high && compare_wordfreq_for_qsort(&arr[high], &pivot) > 0) {
            high--;
        }

        if (low < high) { // low와 high가 교차하지 않았으면, arr[low]와 arr[high]를 교환
            swap_wordfreq(&arr[low], &arr[high]);
        }
    }

    // 피벗(arr[left])과 arr[high]를 교환 (high가 최종 피벗 위치가 됨)
    // 루프 종료 조건상 high는 피벗보다 작거나 같은 요소들의 구역의 마지막을 가리키게 됨
    swap_wordfreq(&arr[left], &arr[high]);
    return high; // 피벗의 최종 위치 반환
}

// 퀵 정렬 주 함수 (qsort.h에 선언됨)
void quickSortFreq(WordFreq arr[], int left, int right) {
    if (left < right) { // 정렬할 요소가 2개 이상인 경우
        if (arr == NULL || left < 0 || right < 0 ) {
            // 기본적인 입력 유효성 검사 (필요에 따라 추가)
            // printf("잘못된 배열 또는 인덱스\n");
            return;
        }
        int q = partitionFreq(arr, left, right); // 피벗을 중심으로 분할

        quickSortFreq(arr, left, q - 1);    // 왼쪽 부분 배열 정렬
        quickSortFreq(arr, q + 1, right);   // 오른쪽 부분 배열 정렬
    }
}