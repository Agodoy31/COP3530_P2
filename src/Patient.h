//
// Created by Sai Rajan on 7/9/26.
//

#pragma once
#include <string>
using namespace std;
//define Patient Struct with patient info for reference
struct Patient
{
    int patient_id;
    int age;
    string gender;
    string blood_type;
    string condition;
    string date_of_admission;
    string doctor;
    string hospital;
    string insurance_provider;
    double billing_amount;
};
