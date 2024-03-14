#include <iostream>
#include "myStack.h"

using namespace myStack;

int main() {
    Stack<int> stack;

    stack.push(5);
    stack.push(10);

    std::cout << "Top element: " << stack.top() << std::endl;

    stack.pop();

    std::cout << "Top element after pop: " << stack.top() << std::endl;

    return 0;
}