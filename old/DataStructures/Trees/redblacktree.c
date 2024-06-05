//  Red Black Tree
//  Game System
//  Grady White
//  1/8/22

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "redblacktree.h"

void RB_insert(Node *root, Node *node, bool dir) {
    Node *T = root;
    Node *N = node;
    Node *P = node->parent;

    Node *G;
    Node *U;

    N->color = RED;
    N->left = NIL;
    N->right = NIL;
    N->parent = P;
}

void RB_rotate(Node *root, Node *node, bool dir)
{
    Node *G = node->parent;
    Node *S = node->child[1-dir];
    Node *C;
    assert(S != NIL);
    C = S->child[dir];
    node->child[1-dir] = C; if (C != NIL) C->parent = node;
    S->child[dir] = node; node->parent = S;
    S->parent = G;
    if (G != NIL)
        G->child[node == G->right ? RIGHT : LEFT] = S;
    else
        root = S;
}