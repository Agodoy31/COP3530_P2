#pragma once
#include <string>
#include <vector>

struct SplayNode {
    int patientID;
    short age;
    char gender;
    std::string bloodType;
    std::string condition;
    std::string dateOfAdmission;
    std::string doctor;
    std::string hospital;
    std::string insuranceProvider;
    double billingAmount;

    SplayNode* left = nullptr;
    SplayNode* right = nullptr;
    SplayNode* parent = nullptr;

    SplayNode(int id, short a, char g, std::string bType, std::string cond,
        std::string date, std::string doc, std::string hosp,
        std::string ins, double bill)
        : patientID(id), age(a), gender(g), bloodType(std::move(bType)),
        condition(std::move(cond)), dateOfAdmission(std::move(date)),
        doctor(std::move(doc)), hospital(std::move(hosp)),
        insuranceProvider(std::move(ins)), billingAmount(bill) {}
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

    void insert(int id, short a, char g, std::string bType, std::string cond, std::string date, std::string doc, std::string hosp, std::string insuranceProvider, double bill);

    std::vector<SplayNode*> searchAge(short targetAge);
    std::vector<SplayNode*> searchAgeRange(short minAge, short maxAge);

    //Recursive helpers
    void destroyTree(SplayNode* node);
    void searchAgeHelper(SplayNode* node, short targetAge, std::vector<SplayNode*> &results);
    void searchAgeRangeHelper(SplayNode* node, short minAge, short maxAge, std::vector<SplayNode*> &results);
};