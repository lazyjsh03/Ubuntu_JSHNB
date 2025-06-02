// bst.c
#include "bst.h"

// 새로운 BST 노드를 생성하는 함수
TNode* create_node(WordFreq item) {
    TNode* n = (TNode*)malloc(sizeof(TNode));
    if (n == NULL) {
        perror("메모리 할당 오류 (create_node)");
        exit(EXIT_FAILURE); // 오류 시 프로그램 종료
    }
    n->data = item; // WordFreq 구조체 데이터 복사
    n->left = NULL;
    n->right = NULL;
    return n;
}

// BST에 단어를 삽입하는 함수
TNode* insert_bst(TNode* root, WordFreq item) {
    if (root == NULL) { // 트리가 비어있거나 삽입 위치에 도달한 경우
        return create_node(item); // 새 노드 생성
    }
    if (strcmp(item.word, root->data.word) < 0) { // 삽입할 단어가 현재 노드 단어보다 작으면 왼쪽으로
        root->left = insert_bst(root->left, item);
    } else if (strcmp(item.word, root->data.word) > 0) { // 삽입할 단어가 현재 노드 단어보다 크면 오른쪽으로
        root->right = insert_bst(root->right, item);
    } else { // 단어가 이미 트리에 존재하면 빈도수만 증가
        root->data.freq++;
    }
    return root;
}

// BST에서 특정 단어를 검색하여 WordFreq 데이터의 포인터 반환
WordFreq* search_bst(TNode* root, const char* wordKey) {
    if (root == NULL) {
        return NULL;
    }
    if (strcmp(wordKey, root->data.word) < 0) {
        return search_bst(root->left, wordKey);
    } else if (strcmp(wordKey, root->data.word) > 0) {
        return search_bst(root->right, wordKey);
    } else {
        return &(root->data); // 단어 찾음, 데이터 주소 반환
    }
}

// BST의 노드 수를 세는 함수
int count_bst_nodes(TNode* n) {
    if (n == NULL) {
        return 0;
    }
    return 1 + count_bst_nodes(n->left) + count_bst_nodes(n->right);
}

// BST를 후위 순회하며 모든 노드의 메모리를 해제하는 함수
void delete_tree(TNode* n) {
    if (n != NULL) {
        delete_tree(n->left);
        delete_tree(n->right);
        free(n);
    }
}

// BST를 중위 순회하여 정렬, WordFreq 데이터들의 개수 반환
int inorder_bst(TNode* n, WordFreq arr[], int count) {
    if (n != NULL) {
        count = inorder_bst(n->left, arr, count);
        arr[count++] = n->data;
        count = inorder_bst(n->right, arr, count);
    }
    return count;
}