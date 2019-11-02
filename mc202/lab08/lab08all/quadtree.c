#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quadtree.h"

qtree* qtree_create(int width, int height, int maxDepth, 
        int maxObjectsPerNode) {
    return NULL;
}

void qtree_destroy(qtree *t) {
}

void qtree_destroyNodes(qnode *root) {
}

int qtree_getIndex(qnode *n, double x, double y, double w, double h) {
    return -1;
}

void qtree_split(qnode *n) {
}

qnode* qtree_createNode(int x, int y, int w, int h, int maxObjects, int level) {
    return NULL;
}

void qtree_insert(qtree *tree, qnode *treeNode, ball *b) {
}

void qtree_retrieve(qnode *root, double x, double y, double w, double h, list *objects) {
}
