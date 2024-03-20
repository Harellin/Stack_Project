cmake_minimum_required(VERSION 3.2)
project(Project2)

set(CMAKE_CXX_STANDARD 17)

add_library(myStack myStack/myStack.h myStack/myStack.cpp myStack/test.cpp)
target_link_libraries(myStack)
add_executable(main main.cpp build/test.cpp build/test.cpp parser.h myStack/myStack.cpp Command.h myStack/myStack.cpp Command.h)
target_link_libraries(main myStack)

