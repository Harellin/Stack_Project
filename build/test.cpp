#include <gtest/gtest.h>
#include <exception>
#include <string>

#include "myStack.h"
TEST(Push, PushIn) {
Stack<int> first;

EXPECT_NO_THROW(first
.Push(123)) << "Исключение";
EXPECT_NO_THROW(first
.Push(23)) << "Исключение";
EXPECT_NO_THROW(first
.Push(12300)) << "Исключение";
EXPECT_NO_THROW(first
.Push(123000)) << "Исключение";

for (
int i = 0;
i < 100; i++) {
EXPECT_NO_THROW(first
.Push(123000)) << "Исключение";
}

}