cmake_minimum_required(VERSION 3.14)
project(Project2 VERSION 0.1.0 LANGUAGES C CXX)
include_directories(./include)

set(SOURCE_LIB ./myStack.cpp)
set(HEADER_LIB ./myStack.h)

add_library(myStack ${SOURCE_LIB} ${HEADER_LIB})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests test/tests.cpp)
target_link_libraries(tests myStack GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)