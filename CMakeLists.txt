cmake_minimum_required(VERSION 3.14)
project(MedicalDatabaseProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 
)
FetchContent_MakeAvailable(Catch2)

# Production Executable
add_executable(Main 
    src/main.cpp 
    src/SplayTree.cpp
)

# Splay Tree Catch2 Unit Tests
add_executable(TestSplay 
    test/test_splay.cpp 
    src/SplayTree.cpp 
 )
target_link_libraries(TestSplay PRIVATE Catch2::Catch2WithMain)

# Skip List Catch2 Unit Tests
add_executable(TestSkipList 
    test/test_skiplist.cpp
 )
target_link_libraries(TestSkipList PRIVATE Catch2::Catch2WithMain)

# Menu & Full Integration Tests
add_executable(TestMenu 
    test/test_menu.cpp 
    src/SplayTree.cpp
)
target_link_libraries(TestMenu PRIVATE Catch2::Catch2WithMain)