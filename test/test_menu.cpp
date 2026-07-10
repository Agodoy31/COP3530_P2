#include <catch2/catch_test_macros.hpp>
#include "../src/menu.h"
#include <fstream>
#include <filesystem>

TEST_CASE("Integer Parsing Validation", "[MenuUtils]") {
    REQUIRE(parseValidInt("42") == 42);

    REQUIRE(parseValidInt("0") == 0);

    REQUIRE(parseValidInt("abc") == -1);

    REQUIRE(parseValidInt("!@#$") == -1);

    REQUIRE(parseValidInt("999999999999999999999999999") == -1);
}

TEST_CASE("File Path Validation and Sanitization", "[MenuUtils]") {
    std::string dummyName = "temp_test_dataset.csv";
    std::ofstream dummyFile(dummyName);
    dummyFile << "dummy data";
    dummyFile.close();

    SECTION("Valid path without quotes") {
        std::string path = dummyName;
        REQUIRE(isValidFilePath(path) == true);
        REQUIRE(path == dummyName);
    }

    SECTION("Valid path with Windows quotes") {
        std::string path = "\"" + dummyName + "\"";
        REQUIRE(isValidFilePath(path) == true);
        REQUIRE(path == dummyName);
    }

    SECTION("Invalid path") {
        std::string path = "does_not_exist.csv";
        REQUIRE(isValidFilePath(path) == false);
    }

    SECTION("Invalid path with quotes") {
        std::string path = "\"fake_file.csv\"";
        REQUIRE(isValidFilePath(path) == false);
        REQUIRE(path == "fake_file.csv");
    }

    std::filesystem::remove(dummyName);
}

TEST_CASE("Age Range Validation", "[MenuUtils]") {
    REQUIRE(isValidAgeRange(45, 50) == true);
    REQUIRE(isValidAgeRange(30, 30) == true);
    REQUIRE(isValidAgeRange(0, 100) == true);

    REQUIRE(isValidAgeRange(50, 45) == false);
    REQUIRE(isValidAgeRange(-5, 20) == false);
    REQUIRE(isValidAgeRange(20, -5) == false);
}

TEST_CASE("Dataset Loading and Parsing", "[MenuUtils]") {
    std::string validFileName = "temp_valid_dataset.csv";
    std::ofstream validFile(validFileName);
    validFile << "patientID,age,gender,bloodType,condition,dateOfAdmission,doctor,hospital,insuranceProvider,billingAmount\n";
    validFile << "100001,32,Male,AB+,COPD,2022-07-03,Dr. Sophia Patel,St. Mary's Hospital,UnitedHealthcare,29627.0\n";
    validFile << "100002,22,Male,A-,COPD,2022-08-10,Dr. Isabella Nguyen,Central City Hospital,Blue Cross Blue Shield,28171.94\n";
    validFile.close();

    std::string invalidFileName = "temp_invalid_dataset.csv";
    std::ofstream invalidFile(invalidFileName);
    invalidFile << "patientID,age,gender,bloodType,condition,dateOfAdmission,doctor,hospital,insuranceProvider,billingAmount\n";
    invalidFile << "100001,THIRTY_TWO,Male,AB+,COPD,2022-07-03,Dr. Sophia Patel,St. Mary's Hospital,UnitedHealthcare,29627.0\n"; // Corrupted age
    invalidFile.close();

    SECTION("Successfully loads a valid dataset") {
        REQUIRE(loadDataset(validFileName) == true);
    }

    SECTION("Fails strictly on a corrupted dataset") {
        REQUIRE(loadDataset(invalidFileName) == false);
    }

    std::filesystem::remove(validFileName);
    std::filesystem::remove(invalidFileName);
}