//
// Created by Sai Rajan on 7/9/26.
//

#ifndef MEDICALDATABASEPROJECT_PATIENT_H
#define MEDICALDATABASEPROJECT_PATIENT_H
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



#endif //MEDICALDATABASEPROJECT_PATIENT_H
