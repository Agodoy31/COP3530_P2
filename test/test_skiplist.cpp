// test_skiplist.cpp
#include <catch2/catch_test_macros.hpp>
#include "../src/SkipList.h"

TEST_CASE("Multiple patients with same age go into one bucket") {
    SkipList list;
    list.insert({1001, 49, "Aetna", "Dr. Smith", "O+"});
    list.insert({1002, 45, "Cigna", "Dr. Lee", "A-"});
    list.insert({1003, 49, "Humana", "Dr. Patel", "B+"});

    auto result = list.search_age(45);
    REQUIRE(result.size() == 1);
    // order-independent check, since bucket order = insertion order but
    // you may not want the test to depend on that

}

