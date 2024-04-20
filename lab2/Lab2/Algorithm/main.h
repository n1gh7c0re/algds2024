//#pragma once
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct Node {
    int key, priority;
    struct Node* left, * right, * parent;
} Node;

typedef struct Treap {
    Node* root;
} Treap;

Node* newNode(int key, int priority) {
    Node* temp = (Node*)malloc(sizeof(Node));
    if (temp) {
        temp->key = key;
        temp->priority = priority;
        temp->left = NULL;
        temp->right = NULL;
        temp->parent = NULL;
        return temp;
    };
}

void rotateRight(Treap* Treap, Node* node) {
    Node* temp = node->left;
    node->left = temp->right;
    if (temp->right != NULL) {
        temp->right->parent = node;
    }

    temp->parent = node->parent;
    if (node->parent == NULL) {
        Treap->root = temp;
    }
    else if (node == node->parent->right) {
        node->parent->right = temp;
    }
    else {
        node->parent->left = temp;
    }

    temp->right = node;
    node->parent = temp;
}

void rotateLeft(Treap* Treap, Node* node) {
    Node* temp = node->right;
    node->right = temp->left;
    if (temp->left != NULL) {
        temp->left->parent = node;
    }

    temp->parent = node->parent;
    if (node->parent == NULL) {
        Treap->root = temp;
    }
    else if (node == node->parent->left) {
        node->parent->left = temp;
    }
    else {
        node->parent->right = temp;
    }

    temp->left = node;
    node->parent = temp;
}

void AddNode(Treap* Treap, int key, int priority) {
    Node* NewNode = newNode(key, priority);
    Node* parent = NULL;
    Node* current = Treap->root;

    while (current != NULL) {
        parent = current;
        if (NewNode->key < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    NewNode->parent = parent;
    if (parent == NULL) {
        Treap->root = NewNode;
    }
    else if (NewNode->key < parent->key) {
        parent->left = NewNode;
    }
    else {
        parent->right = NewNode;
    }

    while (NewNode != Treap->root && NewNode->priority > NewNode->parent->priority) {
        if (NewNode->parent->left == NewNode) {
            rotateRight(Treap, NewNode->parent);
        }
        else {
            rotateLeft(Treap, NewNode->parent);
        }
    }
}

void DeleteNode(Treap* Treap, int key) {
    Node* node = Treap->root;
    while (node != NULL && node->key != key) {
        if (key < node->key) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    if (node == NULL) {
        return; // key not found
    }

    while (node->left != NULL || node->right != NULL) {
        if (node->right == NULL || (node->left != NULL && node->left->priority > node->right->priority)) {
            rotateRight(Treap, node);
        }
        else {
            rotateLeft(Treap, node);
        }
    }

    if (node->parent == NULL) {
        Treap->root = NULL;
    }
    else if (node == node->parent->left) {
        node->parent->left = NULL;
    }
    else {
        node->parent->right = NULL;
    }

    free(node);
}

// Prints Treap in one line
void ResultInOrder(Node* root) {
    if (root != NULL) {
        ResultInOrder(root->left);
        printf("(%d, %d) ", root->key, root->priority);
        ResultInOrder(root->right);
    }
}

// Prints Treap structure
void printTree(Node* root, int space) {
    if (root == NULL) {
        return;
    }
    space += 3;
    printTree(root->right, space);
    printf("\n");
    for (int i = 3; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->key);
    printTree(root->left, space);
}

void Interface(Treap Treap) {
    int n = 0;
    printf("Enter the number of nodes you want to add: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int arr[2] = { 0 };
        printf("Enter the key and priority by space: ");
        scanf("%d %d", &arr[0], &arr[1]);
        AddNode(&Treap, arr[0], arr[1]);
    }

    printf("Inorder traversal of the Treap: ");
    ResultInOrder(Treap.root);
    printf("\n");
    printTree(Treap.root, 0);

    int m = 0;
    printf("\nEnter the number of nodes you want to delete: ");
    scanf("%d", &m);
    if (m != 0){
        for (int i = 0; i < m; i++) {
            int node = 0;
            printf("Enter the node you want to delete: ");
            scanf("%d", &node);
            DeleteNode(&Treap, node);
        }

        printf("Inorder traversal of the Treap after deleting: ");
        ResultInOrder(Treap.root);
        printf("\n");
        printTree(Treap.root, 0);
    }
    else printf("No changes");
};