#pragma once
#include <string>

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
public:
    SplayNode* root;
    int totalNodes;
    int nodesTraversed;

    void leftRotate(SplayNode* x);
    void rightRotate(SplayNode* x);
    void splay(SplayNode* x);

    SplayTree();

    int getNodesTraversed();
    void resetNodesTraversed();
    size_t getMemoryUsageInBytes();
};