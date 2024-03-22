cmake_minimum_required(VERSION 3.2)
project(Project2)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(myStack)
add_executable(main main.cpp build/test.cpp build/test.cpp parser.h myStack/myStack.h PreProc/Command.h PreProc/Command.h PreProc/Token.h)
target_link_libraries(main Stack)

