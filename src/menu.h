#pragma once
#include <string>
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include "SplayTree.h"
#include "SkipList.h"
#include <algorithm>

bool isValidFilePath(std::string& path) {
    if (path.starts_with('"') && path.ends_with('"') && path.length() >= 2) {
        path = path.substr(1, path.length() - 2);
    }

    return std::filesystem::exists(path) && !std::filesystem::is_directory(path);
}

int parseValidInt(const std::string& input) {
    try {
        return std::stoi(input);
    }
    catch (const std::invalid_argument&) {
        return -1;
    }
    catch (const std::out_of_range&) {
        return -1;
    }
}

bool isValidAgeRange(int minAge, int maxAge) {
    return ((minAge >= 0) &&( maxAge >= 0)) && (minAge <= maxAge);
}

void displayMenu() {
    std::cout << "==================================================\n";
    std::cout << "         HEALTHCARE DATABASE SYSTEM MENU\n";
    std::cout << "==================================================\n";
    std::cout << "1. Load Patient Dataset\n";
    std::cout << "2. Exact Patient Lookup (by Age)\n";
    std::cout << "3. Demographic Range Query (by Age)\n";
    std::cout << "4. Exit\n";
    std::cout << "==================================================\n";
    std::cout << "Enter your choice (1-4): ";
}

bool loadDataset(const std::string& filePath, SplayTree& splayTree, SkipList& skipList) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return false;
    }

    std::string header;
    if (!std::getline(file, header)) {
        return false;
    }

    std::string line;
    int recordCount = 0;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string tempID, tempAge, tempGender, bloodType, condition, dateOfAdmission, doctor, hospital, insuranceProvider, tempBilling;

        std::getline(ss, tempID, ',');
        std::getline(ss, tempAge, ',');
        std::getline(ss, tempGender, ',');
        std::getline(ss, bloodType, ',');
        std::getline(ss, condition, ',');
        std::getline(ss, dateOfAdmission, ',');
        std::getline(ss, doctor, ',');
        std::getline(ss, hospital, ',');
        std::getline(ss, insuranceProvider, ',');
        std::getline(ss, tempBilling, ',');

        try {
            Patient p;
            p.patient_id = std::stoi(tempID);
            p.age = std::stoi(tempAge);
            p.gender = tempGender;
            p.blood_type = bloodType;
            p.condition = condition;
            p.date_of_admission = dateOfAdmission;
            p.doctor = doctor;
            p.hospital = hospital;
            p.insurance_provider = insuranceProvider;
            p.billing_amount = std::stod(tempBilling);

            splayTree.insert(p);
            skipList.insert(p);

            recordCount++;
        }
        catch (const std::invalid_argument&) {
            return false;
        }
        catch (const std::out_of_range&) {
            return false;
        }
    }

    file.close();
    std::cout << "\nSuccessfully parsed and loaded " << recordCount << " patient records into both data structures!\n";
    return true;
}

void handleExactLookup(int targetAge, SplayTree& splayTree, SkipList& skipList) {
    splayTree.resetNodesTraversed();
    skipList.reset_nodes_traversed();

    auto splayStart = std::chrono::high_resolution_clock::now();
    std::vector<Patient> splayResults = splayTree.searchAge(static_cast<short>(targetAge));
    auto splayEnd = std::chrono::high_resolution_clock::now();
    auto splayDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(splayEnd - splayStart).count();

    auto skipStart = std::chrono::high_resolution_clock::now();
    std::vector<Patient> skipResults = skipList.search_age(targetAge);
    auto skipEnd = std::chrono::high_resolution_clock::now();
    auto skipDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(skipEnd - skipStart).count();

    std::cout << "\n[Patient Records Found: " << splayResults.size() << "]\n";
    int printLimit = std::min((int)splayResults.size(), 5);
    for(int i = 0; i < printLimit; i++) {
        std::cout << "ID: " << splayResults[i].patient_id << " | Age: " << splayResults[i].age
                  << " | Gender: " << splayResults[i].gender << " | Condition: " << splayResults[i].condition << "\n";
    }
    if (splayResults.size() > 5) {
        std::cout << "... and " << splayResults.size() - 5 << " more patients.\n";
    }

    std::cout << "\n==================================================\n";
    std::cout << "             PERFORMANCE COMPARISON\n";
    std::cout << "==================================================\n";
    std::cout << "Splay Tree Search Time : " << splayDuration << " nanoseconds\n";
    std::cout << "Splay Nodes Traversed  : " << splayTree.getNodesTraversed() << "\n";
    std::cout << "Skip List Search Time  : " << skipDuration << " nanoseconds\n";
    std::cout << "Skip List Nodes Traversed : " << skipList.get_nodes_traversed() << "\n";
    std::cout << "==================================================\n";
}

void handleRangeQuery(int minAge, int maxAge, SplayTree& splayTree, SkipList& skipList) {
    splayTree.resetNodesTraversed();
    skipList.reset_nodes_traversed();

    auto splayStart = std::chrono::high_resolution_clock::now();
    std::vector<Patient> splayResults = splayTree.searchAgeRange(static_cast<short>(minAge), static_cast<short>(maxAge));
    auto splayEnd = std::chrono::high_resolution_clock::now();
    auto splayDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(splayEnd - splayStart).count();

    auto skipStart = std::chrono::high_resolution_clock::now();
    std::vector<Patient> skipResults = skipList.search_age_range(minAge, maxAge);
    auto skipEnd = std::chrono::high_resolution_clock::now();
    auto skipDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(skipEnd - skipStart).count();

    std::cout << "\n[Patient Records Found: " << splayResults.size() << "]\n";
    int printLimit = std::min((int)splayResults.size(), 5);
    for(int i = 0; i < printLimit; i++) {
        std::cout << "ID: " << splayResults[i].patient_id << " | Age: " << splayResults[i].age
                  << " | Gender: " << splayResults[i].gender << " | Condition: " << splayResults[i].condition << "\n";
    }
    if (splayResults.size() > 5) {
        std::cout << "... and " << splayResults.size() - 5 << " more patients.\n";
    }


    std::cout << "\n==================================================\n";
    std::cout << "             PERFORMANCE COMPARISON\n";
    std::cout << "==================================================\n";
    std::cout << "Splay Tree Search Time : " << splayDuration << " nanoseconds\n";
    std::cout << "Splay Nodes Traversed  : " << splayTree.getNodesTraversed() << "\n";
    std::cout << "Skip List Search Time  : " << skipDuration << " nanoseconds\n";
    std::cout << "Skip List Nodes Traversed : " << skipList.get_nodes_traversed() << "\n";
    std::cout << "==================================================\n";
}

void runMenu() {
    bool isDatasetLoaded = false;
    SplayTree splayTree;
    SkipList skipList;
    std::cout << "Welcome to the Healthcare Database System!\n";
    std::cout << "This application compares Splay Tree and Skip List performance.\n\n";

    while (true) {
        displayMenu();

        std::string choiceInput;
        std::getline(std::cin, choiceInput);
        int choice = parseValidInt(choiceInput);

        if (choice == 4) {
            std::cout << "\nExiting application. Goodbye!\n";
            break;
        }
        else if (choice == 1) {
            std::string path;
            std::cout << "Enter the dataset file path: ";
            std::getline(std::cin, path);

            if (isValidFilePath(path)) {
                if (loadDataset(path, splayTree, skipList)) {
                    isDatasetLoaded = true;
                }
                else {
                    std::cout << "Error: Failed to parse dataset.\n";
                }
            }
            else {
                std::cout << "Error: File not found or invalid path. Returning to main menu.\n";
            }
        }
        else if (choice == 2) {
            if (!isDatasetLoaded) {
                std::cout << "\nError: You must load the dataset first (Option 1)!\n";
            }
            else {
                std::cout << "Enter Patient age to lookup: ";
                std::string inputAge;
                std::getline(std::cin, inputAge);
                int age = parseValidInt(inputAge);

                if (age == -1 || age < 0) {
                    std::cout << "Error: Invalid Patient Age. Please enter a valid positive number.\n";
                }
                else {
                    handleExactLookup(age, splayTree, skipList);
                }
            }
        }
        else if (choice == 3) {
            if (!isDatasetLoaded) {
                std::cout << "\nError: You must load the dataset first (Option 1)!\n";
            }
            else {
                std::string inputMin, inputMax;
                std::cout << "Enter minimum age: ";
                std::getline(std::cin, inputMin);
                int minAge = parseValidInt(inputMin);

                std::cout << "Enter maximum age: ";
                std::getline(std::cin, inputMax);
                int maxAge = parseValidInt(inputMax);

                if (minAge == -1 || maxAge == -1 || !isValidAgeRange(minAge, maxAge)) {
                    std::cout << "Error: Invalid age range. Ages must be positive and min age <= max age.\n";
                }
                else {
                    handleRangeQuery(minAge, maxAge, splayTree, skipList);
                }
            }
        }
        else {
            std::cout << "\nError: Invalid choice. Please enter a number between 1 and 4.\n";
        }

        std::cout << "\nPress Enter to continue...";
        std::string dummy;
        std::getline(std::cin, dummy);
        std::cout << "\n==================================================\n\n";
    }
}