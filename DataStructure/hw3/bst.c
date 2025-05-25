#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

// 새로운 BST 노드를 생성하는 함수
// WordFreq 데이터를 받아 노드를 생성.
TNode* create_bst_node(WordFreq item) {
    TNode* n = (TNode*)malloc(sizeof(TNode));
    if (n == NULL) {
        perror("메모리 할당 오류 (create_bst_node)");
        exit(0);
    }
    n->data = item; // WordFreq 구조체 데이터를 노드에 저장
    n->left = NULL;
    n->right = NULL;
    return n;
}

// BST 모든 노드의 메모리를 해제하는 함수
void delete_bst_tree(TNode* n) {
    if (n != NULL) {
        delete_bst_tree(n->left);  // 왼쪽 서브트리 삭제
        delete_bst_tree(n->right); // 오른쪽 서브트리 삭제
        free(n);                   // 현재 노드 삭제
    }
}

// BST에 단어를 삽입하는 함수
// 단어가 이미 존재하면 빈도수를 증가시키고, 새로운 단어면 노드를 추가.
TNode* insert_word_bst(TNode* root, WordFreq item) {
    // 트리가 비어있거나, 삽입 위치에 도달한 경우
    if (root == NULL) {
        // item.freq는 보통 1로 초기화되어 전달될 것입니다.
        // 만약 이 함수 내에서 새 단어의 빈도수를 1로 설정해야 한다면,
        // item을 받기 전에 item.freq = 1; 처리를 해야 합니다.
        // 여기서는 item에 이미 적절한 freq가 설정되어 있다고 가정합니다.
        return create_bst_node(item);
    }

    // 단어 비교
    int cmp = strcmp(item.word, root->data.word);

    if (cmp < 0) { // 삽입할 단어가 현재 노드의 단어보다 작으면 왼쪽으로
        root->left = insert_word_bst(root->left, item);
    } else if (cmp > 0) { // 삽입할 단어가 현재 노드의 단어보다 크면 오른쪽으로
        root->right = insert_word_bst(root->right, item);
    } else { // 단어가 이미 트리에 존재하면 빈도수만 증가
        root->data.freq++;
    }
    return root;
}

// BST에서 특정 단어를 검색하는 함수
// 찾으면 해당 노드의 WordFreq 데이터 포인터를 반환하고, 없으면 NULL을 반환.
WordFreq* search_word_bst(TNode* root, const char* word_key) {
    if (root == NULL) {
        return NULL; // 단어를 찾지 못함
    }

    int cmp = strcmp(word_key, root->data.word);

    if (cmp < 0) {
        return search_word_bst(root->left, word_key);
    } else if (cmp > 0) {
        return search_word_bst(root->right, word_key);
    } else {
        return &(root->data); // 단어를 찾음, 해당 데이터의 주소 반환
    }
}

// BST를 중위 순회하며 WordFreq 데이터를 배열에 저장하는 함수
// count는 배열에 현재까지 저장된 요소의 수를 추적합니다.
int inorder_bst_to_array(TNode* n, WordFreq arr[], int count) {
    if (n != NULL) {
        count = inorder_bst_to_array(n->left, arr, count); // 왼쪽 서브트리 순회
        
        // 배열 크기를 초과하지 않도록 주의해야 합니다.
        // 실제 사용 시에는 배열의 최대 크기를 인자로 받아 확인하는 로직이 필요합니다.
        arr[count++] = n->data; // 현재 노드의 데이터를 배열에 저장 (구조체 복사)
        
        count = inorder_bst_to_array(n->right, arr, count); // 오른쪽 서브트리 순회
    }
    return count; // 업데이트된 요소의 수 반환
}


// BST의 노드 수를 세는 함수 (고유 단어 수 계산)
int count_bst_nodes(TNode* n) {
    if (n == NULL) {
        return 0;
    }
    return 1 + count_bst_nodes(n->left) + count_bst_nodes(n->right);
}
