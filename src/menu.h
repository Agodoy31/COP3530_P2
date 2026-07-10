#pragma once
#include <string>
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>

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
    std::cout << "2. Exact Patient Lookup (by Patient ID)\n";
    std::cout << "3. Demographic Range Query (by Age)\n";
    std::cout << "4. Exit\n";
    std::cout << "==================================================\n";
    std::cout << "Enter your choice (1-4): ";
}

bool loadDataset(const std::string& filePath) {
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
            int id = std::stoi(tempID);
            short age = static_cast<short>(std::stoi(tempAge));
            char gender = tempGender.empty() ? 'U' : tempGender[0];
            double billing = std::stod(tempBilling);

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
    std::cout << "\nSuccessfully parsed and loaded " << recordCount << " patient records (Mocked)!\n";
    return true;
}

void handleExactLookup(int patientID) {
    auto splayStart = std::chrono::high_resolution_clock::now();
    std::cout << "\n[Splay Tree Search] Searching for Patient ID: " << patientID << "...\n";
    auto splayEnd = std::chrono::high_resolution_clock::now();
    auto splayDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(splayEnd - splayStart).count();

    auto skipStart = std::chrono::high_resolution_clock::now();
    std::cout << "[Skip List Search] Searching for Patient ID: " << patientID << "...\n";
    auto skipEnd = std::chrono::high_resolution_clock::now();
    auto skipDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(skipEnd - skipStart).count();

    std::cout << "\n[Patient Record Found]\n";
    std::cout << "ID: " << patientID << "\n";
    std::cout << "Age: 32\n";
    std::cout << "Gender: Male\n";
    std::cout << "Condition: COPD\n";
    std::cout << "Billing Amount: $29627.00\n";

    std::cout << "\n==================================================\n";
    std::cout << "             PERFORMANCE COMPARISON\n";
    std::cout << "==================================================\n";
    std::cout << "Splay Tree Search Time : " << splayDuration << " nanoseconds\n";
    std::cout << "Skip List Search Time  : " << skipDuration << " nanoseconds\n";
    std::cout << "==================================================\n";
}

void handleRangeQuery(int minAge, int maxAge) {
    auto splayStart = std::chrono::high_resolution_clock::now();
    std::cout << "\n[Splay Tree Search] Querying patients between ages " << minAge << " and " << maxAge << "...\n";
    auto splayEnd = std::chrono::high_resolution_clock::now();
    auto splayDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(splayEnd - splayStart).count();

    auto skipStart = std::chrono::high_resolution_clock::now();
    std::cout << "[Skip List Search] Querying patients between ages " << minAge << " and " << maxAge << "...\n";
    auto skipEnd = std::chrono::high_resolution_clock::now();
    auto skipDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(skipEnd - skipStart).count();

    std::cout << "\n[Patient Records Found (Mocked)]\n";
    std::cout << "ID: 100001 | Age: 32 | Gender: Male | Condition: COPD | Billing: $29627.00\n";
    std::cout << "ID: 100004 | Age: 37 | Gender: Male | Condition: Type 2 Diabetes | Billing: $42412.84\n";

    std::cout << "\n==================================================\n";
    std::cout << "             PERFORMANCE COMPARISON\n";
    std::cout << "==================================================\n";
    std::cout << "Splay Tree Search Time : " << splayDuration << " nanoseconds\n";
    std::cout << "Skip List Search Time  : " << skipDuration << " nanoseconds\n";
    std::cout << "==================================================\n";
}

void runMenu() {
    bool isDatasetLoaded = false;
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
                if (loadDataset(path)) {
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
                std::cout << "Enter Patient ID to lookup: ";
                std::string inputID;
                std::getline(std::cin, inputID);
                int id = parseValidInt(inputID);

                if (id == -1) {
                    std::cout << "Error: Invalid Patient ID. Please enter a valid positive number.\n";
                }
                else {
                    handleExactLookup(id);
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
                    handleRangeQuery(minAge, maxAge);
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