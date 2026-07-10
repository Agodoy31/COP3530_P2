#pragma once
#include <string>
#include <vector>
#include "Patient.h"

struct SplayNode {
    Patient patient;

    SplayNode* left = nullptr;
    SplayNode* right = nullptr;
    SplayNode* parent = nullptr;

    SplayNode(const Patient& p) : patient(p) {}
};

class SplayTree {
    // Everything is public for testing purposes. 
public:
    SplayNode* root;
    int totalNodes;
    int nodesTraversed;

    void leftRotate(SplayNode* x);
    void rightRotate(SplayNode* x);
    void splay(SplayNode* x);

    SplayTree();
    ~SplayTree();

    int getNodesTraversed();
    void resetNodesTraversed();
    size_t getMemoryUsageInBytes();

    void insert(const Patient& p);

    std::vector<Patient> searchAge(short targetAge);
    std::vector<Patient> searchAgeRange(short minAge, short maxAge);

    //Recursive helpers
    void destroyTree(SplayNode* node);
    void searchAgeHelper(SplayNode* node, short targetAge, std::vector<Patient>& results);
    void searchAgeRangeHelper(SplayNode* node, short minAge, short maxAge, std::vector<Patient>& results);
};