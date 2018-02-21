#include <stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct node {
    size_t *keys;
    struct node **nodes;
    size_t ksize;
    size_t nsize;
    int leaf;
} node_t;

typedef struct b_tree {
    size_t degree;
    node_t *root;
} Btree_t;

node_t *new_node(size_t degree) {
    node_t *node = malloc(sizeof(node_t));
    if (node == NULL)
        return NULL;
    node->keys = malloc((2 * degree - 1) * sizeof(size_t));
    if (node->keys == NULL)
        return NULL;
    node->nodes = malloc(2 * degree * sizeof(*(node->nodes)));
    if (node->nodes == NULL)
        return NULL;
    node->ksize = 0;
    node->nsize = 0;
    node->leaf = TRUE;

    return node;
}

Btree_t *init_btree(size_t degree) {
    Btree_t *b_tree = malloc(sizeof(Btree_t));
    if (b_tree == NULL)
        return NULL;
    b_tree->degree = degree;
    b_tree->root = new_node(degree);
    if (b_tree->root == NULL) {
        free(b_tree);
        return NULL;
    }
    return b_tree;
}

void btree_split_child(Btree_t *btree, node_t *node, int i) {
    node_t *z = malloc(sizeof(node_t));
    node_t *y = node->nodes[i];
    size_t middle = y->keys[btree->degree - 1];
    z->leaf = y->leaf;
    z->ksize = btree->degree - 1;
    int j, m;
    for (j = 0; j < btree->degree - 1; j++)
        if (!y->leaf)
            for (m = 0, j = j + 1; j < y->nsize; m++, j++)
                z->nodes[m] = y->nodes[j];
    y->ksize = btree->degree - 1;
    for (m = node->ksize - 1; m >= i; m--)
        node->keys[m + 1] = node->keys[m];
    m++;
    node->keys[m] = middle;
    for (m = node->nsize - 1; m >= i + 1; m--)
        node->nodes[m + 1] = node->nodes[m];
    m++;
    node->nodes[m] = z;
    node->ksize++;
}

void btree_insert_nonfull(Btree_t *btree, node_t *node, size_t key) {
    int i = node->ksize;
    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->ksize++;
    } else {
        while (i >= 0 && key < node->keys[i])
            i--;
        i = i + 1;
        if (node->nodes[i]->ksize == (2 * btree->degree - 1)) {
            btree_split_child(btree, node->nodes[i], i);
            if (key > node->keys[i])
                i++;
        }
        btree_insert_nonfull(btree, node->nodes[i], key);
    }
}

ssize_t insert_btree(Btree_t *btree, size_t k) {
    node_t *r = btree->root;
    size_t max = 2 * btree->degree - 1;
    if (r->ksize == max) {
        node_t *s = new_node(btree->degree);
        if (s == NULL)
            return -1;
        s->leaf = FALSE;
        s->nodes[0] = r;
        btree_split_child(btree, s, 0);
        btree_insert_nonfull(btree, s, k);
    } else
        btree_insert_nonfull(btree, r, k);
    return 0;
}
