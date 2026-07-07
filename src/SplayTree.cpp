#include "SplayTree.h"

SplayTree::SplayTree() {
    root = nullptr;
    totalNodes = 0;
    nodesTraversed = 0;
}

int SplayTree::getNodesTraversed() {
    return nodesTraversed;
}

void SplayTree::resetNodesTraversed() {
    nodesTraversed = 0;
}

size_t SplayTree::getMemoryUsageInBytes() {
    return totalNodes * sizeof(SplayNode);
}

void SplayTree::leftRotate(SplayNode* x) {
    SplayNode* y = x->right;
    if (y == nullptr) return;

    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void SplayTree::rightRotate(SplayNode* x) {
    SplayNode* y = x->left;
    if (y == nullptr) return;

    x->left = y->right;
    if (y->right != nullptr) {
        y->right->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}