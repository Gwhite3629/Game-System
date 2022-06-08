//  Red Black Tree Header
//  Game System
//  Grady White
//  1/8/22

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

#define LEFT 0
#define RIGHT 1

#define left child[LEFT]
#define right child[RIGHT]

#define uint unsigned int

typedef struct Node {
    void *data;
    Node *child[2];
    Node *parent;
    bool color;
} Node;

#define NIL NULL

#define ROOT Node *ROOT \
    ROOT->data = NULL; \
    ROOT->child[0] = NIL; \
    ROOT->child[1] = NIL; \
    ROOT->parent = NIL; \
    ROOT->color = BLACK;

// Returns new root of subtree
void RB_rotate(Node *root, // Current root of tree
                Node *node, // Current root of subtree
                bool dir); // Rotation direction

void RB_print(Node *node);
void RB_insert(Node *root,
               Node *node,
               bool dir);
void RB_insert_fixup(Node *node);
Node *RB_search(void *value);
Node *RB_minimum(Node *node);
void RB_remove(Node *node);
void RB_remove_fixup(Node *node);