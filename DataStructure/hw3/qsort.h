#ifndef QSORT_H
#define QSORT_H

#include "bst.h" // WordFreq 구조체 정의를 포함하는 헤더

// WordFreq 배열을 빈도수 기준으로 정렬
void quickSort(WordFreq arr[], int low, int high);

#endif