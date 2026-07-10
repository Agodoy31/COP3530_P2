// test_splay.cpp

#include <catch2/catch_test_macros.hpp>
#include "../src/SplayTree.h"

TEST_CASE("SplayTree Standalone Left Rotation with Root Replacement", "[SplayTree]") {
    SplayTree tree;

    SplayNode* x = new SplayNode(10, 30, 'M', "O+", "Flu", "2025-01-01", "Dr. Smith", "General Hospital", "Blue Cross", 150.0);
    SplayNode* y = new SplayNode(20, 45, 'F', "A-", "Cold", "2025-01-02", "Dr. Jones", "City Clinic", "Aetna", 200.0);
    SplayNode* a = new SplayNode(15, 25, 'M', "B+", "Allergy", "2025-01-03", "Dr. Smith", "General Hospital", "Cigna", 120.0);
    SplayNode* b = new SplayNode(25, 60, 'F', "AB+", "Fever", "2025-01-04", "Dr. Jones", "City Clinic", "United", 310.0);

    x->right = y;
    y->parent = x;

    y->left = a;
    a->parent = y;

    y->right = b;
    b->parent = y;

    tree.root = x;

    tree.leftRotate(x);

    REQUIRE(tree.root == y);
    REQUIRE(y->parent == nullptr);
    REQUIRE(y->left == x);
    REQUIRE(y->right == b);

    REQUIRE(x->parent == y);
    REQUIRE(x->left == nullptr);
    REQUIRE(x->right == a);

    REQUIRE(a->parent == x);
    REQUIRE(b->parent == y);

    delete x;
    delete y;
    delete a;
    delete b;
}

TEST_CASE("SplayTree Standalone Right Rotation with Root Replacement", "[SplayTree]") {
    SplayTree tree;

    SplayNode* x = new SplayNode(20, 45, 'F', "A-", "Cold", "2025-01-02", "Dr. Jones", "City Clinic", "Aetna", 200.0);
    SplayNode* y = new SplayNode(10, 30, 'M', "O+", "Flu", "2025-01-01", "Dr. Smith", "General Hospital", "Blue Cross", 150.0);
    SplayNode* b = new SplayNode(5, 18, 'M', "O-", "Asthma", "2025-01-05", "Dr. Davis", "Childrens", "Humana", 90.0);
    SplayNode* a = new SplayNode(15, 25, 'M', "B+", "Allergy", "2025-01-03", "Dr. Smith", "General Hospital", "Cigna", 120.0);

    x->left = y;
    y->parent = x;

    y->left = b;
    b->parent = y;

    y->right = a;
    a->parent = y;

    tree.root = x;

    tree.rightRotate(x);

    REQUIRE(tree.root == y);
    REQUIRE(y->parent == nullptr);
    REQUIRE(y->left == b);
    REQUIRE(y->right == x);

    REQUIRE(x->parent == y);
    REQUIRE(x->left == a);
    REQUIRE(x->right == nullptr);

    REQUIRE(a->parent == x);
    REQUIRE(b->parent == y);

    delete x;
    delete y;
    delete a;
    delete b;
}

TEST_CASE("SplayTree Standalone Left Rotation on Non-Root Node", "[SplayTree]") {
    SplayTree tree;

    SplayNode* p = new SplayNode(30, 50, 'F', "O+", "Healthy", "2025-01-06", "Dr. Evans", "General Hospital", "Medicare", 50.0);
    SplayNode* x = new SplayNode(10, 30, 'M', "O+", "Flu", "2025-01-01", "Dr. Smith", "General Hospital", "Blue Cross", 150.0);
    SplayNode* y = new SplayNode(20, 45, 'F', "A-", "Cold", "2025-01-02", "Dr. Jones", "City Clinic", "Aetna", 200.0);
    SplayNode* a = new SplayNode(15, 25, 'M', "B+", "Allergy", "2025-01-03", "Dr. Smith", "General Hospital", "Cigna", 120.0);

    p->left = x;
    x->parent = p;

    x->right = y;
    y->parent = x;

    y->left = a;
    a->parent = y;

    tree.root = p;

    tree.leftRotate(x);

    REQUIRE(tree.root == p);
    REQUIRE(p->left == y);

    REQUIRE(y->parent == p);
    REQUIRE(y->left == x);
    REQUIRE(y->right == nullptr);

    REQUIRE(x->parent == y);
    REQUIRE(x->left == nullptr);
    REQUIRE(x->right == a);

    REQUIRE(a->parent == x);

    delete p;
    delete x;
    delete y;
    delete a;
}