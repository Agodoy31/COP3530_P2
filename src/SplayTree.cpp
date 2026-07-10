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

/*
 * Summary: Destructor to free allocated memory
 */
SplayTree::~SplayTree() {
    destroyTree(root);
}

void SplayTree::destroyTree(SplayNode* node) {
    if (node == nullptr) return;

    SplayNode* curr = node;
    while (curr != nullptr) {
        // Traverse down to the leaves
        if (curr->left != nullptr) {
            curr = curr->left;
        }
        else if (curr->right != nullptr) {
            curr = curr->right;
        }
        else {
            // If it's a leaf, delete it and move back up to the parent
            SplayNode* parent = curr->parent;
            if (parent != nullptr) {
                if (parent->left == curr) {
                    parent->left = nullptr;
                }
                else {
                    parent->right = nullptr;
                }
            }
            delete curr;
            curr = parent;
        }
    }
    root = nullptr;
}

/*
 * Summary: Inserts a new patient record into the tree and splays it all the way up to root
 */
void SplayTree::insert(const Patient& p) {

    SplayNode* newNode = new SplayNode(p);
    totalNodes++;

    if (root == nullptr) {
        root = newNode;
        return;
    }

    SplayNode* curr = root;
    SplayNode* parent = nullptr;

    // Standard BST insertion
    while (curr != nullptr) {
        parent = curr;
        nodesTraversed++;
        if (p.age < curr->patient.age) {
            curr = curr->left;
        }
        else {
            // Duplicate ages go right initially
            curr = curr->right;
        }
    }

    newNode->parent = parent;
    if (p.age < parent->patient.age) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }

    // Bubble the inserted node to the root
    splay(newNode);
}

/*
 * Summary: Searches for all patients with an exact age. Splays the first match found.
 */
std::vector<Patient> SplayTree::searchAge(short targetAge) {
    std::vector<Patient> results;
    SplayNode* curr = root;
    SplayNode* match = nullptr;

    // Find the first occurrence to splay it
    while (curr != nullptr) {
        nodesTraversed++;
        if (targetAge == curr->patient.age) {
            match = curr;
            break;
        }
        else if (targetAge < curr->patient.age) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }

    if (match != nullptr) {
        splay(match);
        // Extract all duplicates via traversal
        searchAgeHelper(root, targetAge, results);
    }

    return results;
}

void SplayTree::searchAgeHelper(SplayNode* node, short targetAge, std::vector<Patient>& results) {
    if (node == nullptr) return;

    nodesTraversed++;

    // Check left subtree if target could be there
    if (targetAge <= node->patient.age) {
        searchAgeHelper(node->left, targetAge, results);
    }

    // Process exact match
    if (targetAge == node->patient.age) {
        results.push_back(node->patient);
    }

    // Check right subtree if target could be there
    if (targetAge >= node->patient.age) {
        searchAgeHelper(node->right, targetAge, results);
    }
}

/*
 * Summary: Performs an inorder traversal to collect nodes within an age range
 */
std::vector<Patient> SplayTree::searchAgeRange(short minAge, short maxAge) {
    std::vector<Patient> results;
    searchAgeRangeHelper(root, minAge, maxAge, results);
    return results;
}

void SplayTree::searchAgeRangeHelper(SplayNode* node, short minAge, short maxAge, std::vector<Patient>& results) {
    if (node == nullptr) return;

    nodesTraversed++;

    // Traverse left if there is potential for valid ages
    if (minAge <= node->patient.age) {
        searchAgeRangeHelper(node->left, minAge, maxAge, results);
    }

    // Include node if it falls within the range
    if (node->patient.age >= minAge && node->patient.age <= maxAge) {
        results.push_back(node->patient);
    }

    // Traverse right if there is potential for valid ages
    if (maxAge >= node->patient.age) {
        searchAgeRangeHelper(node->right, minAge, maxAge, results);
    }
}