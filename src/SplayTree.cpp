#include "SplayTree.h"

/*
 * Summary: Initializes an empty splay tree with default values.
 * Inputs: None.
 * Local variables: None.
 * Return: None.
 */
SplayTree::SplayTree() {
    root = nullptr;
    totalNodes = 0;
    nodesTraversed = 0;
}

/*
 * Summary: Retrieves the number of nodes traversed during operations.
 * Inputs: None.
 * Local variables: None.
 * Return: The count of traversed nodes as an integer.
 */
int SplayTree::getNodesTraversed() {
    return nodesTraversed;
}

/*
 * Summary: Resets the traversal counter to zero.
 * Inputs: None.
 * Local variables: None.
 * Return: None.
 */
void SplayTree::resetNodesTraversed() {
    nodesTraversed = 0;
}

/*
 * Summary: Calculates the total memory allocated for the tree nodes.
 * Inputs: None.
 * Local variables: None.
 * Return: The memory usage in bytes as a size_t.
 */
size_t SplayTree::getMemoryUsageInBytes() {
    return totalNodes * sizeof(SplayNode);
}

/*
 * Summary: Performs a left rotation on a given node.
 * Inputs: SplayNode* x the node to rotate around.
 * Local variables:
 *   SplayNode* y: The right child of x which will become the new parent of x.
 * Return: None.
 */
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

/*
 * Summary: Performs a right rotation on a given node.
 * Inputs: SplayNode* x the node to rotate around.
 * Local variables:
 *   SplayNode* y: The left child of x, which will become the new parent of x.
 * Return: None.
 */
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

/*
 * Summary: Splays a target node to the root of the tree using rotations.
 * Inputs: SplayNode* x (the node to splay to the root).
 * Local variables:
 *   SplayNode* p: The parent of the current node.
 *   SplayNode* g: The grandparent of the current node.
 * Return: None.
 */
void SplayTree::splay(SplayNode* x) {
    if (x == nullptr) return;

    while (x->parent != nullptr) {
        SplayNode* p = x->parent;
        SplayNode* g = p->parent;

        if (g == nullptr) {
            if (x == p->left) {
                rightRotate(p);
            }
            else {
                leftRotate(p);
            }
        }
        else {
            if (p == g->left) {
                if (x == p->left) {
                    rightRotate(g);
                    rightRotate(p);
                }
                else {
                    leftRotate(p);
                    rightRotate(g);
                }
            }
            else {
                if (x == p->right) {
                    leftRotate(g);
                    leftRotate(p);
                }
                else {
                    rightRotate(p);
                    leftRotate(g);
                }
            }
        }
    }
}