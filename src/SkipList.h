// SkipList.h
#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Skip List structure: The list has different nodes with the key being the patient age.
// One age node has a vector of Patient objects (called patients), which stores each patient object.
// Insert function requires a patient object to be created, which is passed in **can change so the patient object is
// created before pass-in.** Search queries allow for range based and single-age queries.


//define Patient Struct with patient info
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

//max height of list set to 16 (around log base 2 of 100k)
//probability for coin flip set to 0.5
const int max_level = 16;

//skip list node struct, takes age as key, initializes patient and pointer vectors
struct Node
{
    int age;
    vector<Patient> patients;
    vector<Node*> forward;

    Node(int age, int curr_level) : age(age), forward(curr_level, nullptr)
    {

    }
};
//skip list class uses Nodes, with current level of head set to 0
class SkipList
{
private:
    Node* head;
    int current_level;

    //function that assigns a random level for a new node
    int random_level()
    {
        int new_level = 1;
        while (((float)rand() / RAND_MAX ) < 0.5f && new_level <max_level)
        {
            new_level++;
        }
        return new_level;
    }

public:
    SkipList() : current_level(0)
    {
        head = new Node(-1, max_level);
    }

    //inserts a patient to become a node in the list
    void insert(const Patient& P)
    {

        vector<Node*> update(max_level, nullptr);
        Node* curr = head;

        for (int i = current_level; i >= 0; i--)
        {
            while (curr->forward[i]  && curr->forward[i]->age < P.age)
            {
                curr = curr->forward[i];
            }
            update[i] = curr;
        }

        curr = curr->forward[0];

        //adds patient info to node with Patients information
        if (curr != nullptr && curr->age == P.age)
        {
            curr->patients.push_back(P);
            return;
        }
        //if age is unique, create new node, first gets random level
        int new_level = random_level();
        if (current_level < new_level)
        {
            for (int i = current_level; i < new_level; i++)
            {
                update[i] = head;
            }
            current_level = new_level;
        }
        //create new node and updates the value at each level
        Node* curr_node = new Node(P.age, new_level);
        curr_node->patients.push_back(P);

        for (int i = 0; i < new_level; i++)
        {
            curr_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = curr_node;
        }

    }

    //search function for direct age - returns vector, might need additional functional
    // or implementation to iterate through vector and display patient info
    vector<Patient> search_age(int age)
    {
        //traverses the list iteratively through levels
        Node* curr = head;
        for (int i = current_level; i >= 0; i--)
        {
            while (curr->forward[i] && curr->forward[i]->age < age)
            {
                curr = curr->forward[i];
            }
        }

        //once node is found check if age exists, if not returns empty patient vector
        curr = curr->forward[0];

        if (curr != nullptr && curr->age == age)
        {
            return curr->patients;
        }
        return {}; // no patient match
    }

    //inclusive age range search function, returns patients that fall in range
    vector<Patient> search_age_range(int age_lower, int age_higher)
    {
        vector<Patient> final;
        Node* curr = head;
        for (int i = current_level; i >= 0; i--)
        {
            while (curr->forward[i] && curr->forward[i]->age < age_lower)
            {
                curr = curr->forward[i];
            }
        }
        curr = curr->forward[0];
        while (curr && curr->age <= age_higher)
        {
            for (const Patient& P : curr->patients)
            {
                final.push_back(P);
            }
            curr = curr->forward[0];
        }
        return final;
    }

    //debug print helper function
    void display_list()
    {
        Node* curr = head->forward[0];
        while (curr)
        {
            cout << curr->age << " ( " << curr->patients.size() << " patients ) ";
            curr = curr->forward[0];
        }
        cout << " null" ;
    }

    //destructor

    ~SkipList()
    {
        Node* curr = head;
        while (curr)
        {
            Node* next = curr->forward[0];
            delete curr;
            curr = next;
        }
    }



};


