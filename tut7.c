#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node *left, *right;
};

struct node* newNode(int item) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

void inorder(struct node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

struct node* insert(struct node* node, int key) {
    if (node == NULL) return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    return node;
}

int main() {
    struct node* root = NULL;
    int arr[] = { 50, 30, 20, 40, 70, 60, 80 };
    int n = sizeof(arr) / sizeof(arr[0]);

    for(int i=0; i < n; i++) {
        root = insert(root, arr[i]);
    }

    printf("Sorted numbers: ");
    inorder(root);
    printf("\n");
    return 0;
}