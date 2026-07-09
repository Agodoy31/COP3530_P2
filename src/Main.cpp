// main.cpp
#include "../src/SkipList.h"

int main() {

    SkipList list;
    list.insert({1001, 49, "Aetna", "Dr. Smith", "O+"});
    list.insert({1002, 48, "Cigna", "Dr. Lee", "A-"});
    list.insert({1003, 47, "Humana", "Dr. Patel", "B+"});
    list.insert({1003, 49, "Humana", "Dr. Patel", "B+"});
    list.display_list();






    return 0;
}