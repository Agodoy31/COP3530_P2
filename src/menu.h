#pragma once
#include <string>
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>

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