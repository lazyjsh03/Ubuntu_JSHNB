#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 100 // 단어의 최대 길이

// 단어와 빈도수를 저장하는 구조체
typedef struct {
    char word[MAX_WORD_LEN];
    int freq;
} WordFreq;

// 이진 트리의 노드 구조체
typedef struct TNode {
    WordFreq data;          // 노드에 저장할 자료 (WordFreq 구조체)
    struct TNode* left;     // 왼쪽 서브 트리
    struct TNode* right;    // 오른쪽 서브 트리
} TNode;

// 함수 선언들
TNode* create_bst_node(WordFreq item);
void delete_bst_tree(TNode* n);
TNode* insert_word_bst(TNode* root, WordFreq item);
WordFreq* search_word_bst(TNode* root, const char* word_key);
int inorder_bst_to_array(TNode* n, WordFreq arr[], int count);
int count_bst_nodes(TNode* n);

#endif