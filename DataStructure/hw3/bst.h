#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 100

typedef struct {
    char word[MAX_WORD_LEN];
    int freq;
} WordFreq;

typedef struct TNode {
    WordFreq data;
    struct TNode* left;
    struct TNode* right;
} TNode;

// BST 함수 선언
TNode* create_node(WordFreq item);
void delete_tree(TNode* n);
TNode* insert_bst(TNode* root, WordFreq item); 
WordFreq* search_bst(TNode* root, const char* word_key);
int inorder_bst(TNode* n, WordFreq arr[], int count);
int count_bst_nodes(TNode* n);

#endif