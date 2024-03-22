#include <gtest/gtest.h>
#include <exception>
#include <string>

#include "mystack.h"
using namespace myStack;

TEST(push, PushIn) {
Stack<int> first;

EXPECT_NO_THROW(first.push(123)) << "Исключение";
EXPECT_NO_THROW(first.push(23)) << "Исключение";
EXPECT_NO_THROW(first.push(12300)) << "Исключение";
EXPECT_NO_THROW(first.push(123000)) << "Исключение";

for (int i = 0; i < 100; i++) {
EXPECT_NO_THROW(first.push(123000)) << "Исключение";
}

}

TEST(Pop, PopOut) {
Stack<int> first;

for (int i = 0; i < 100; i++) {
first.push(123000);
}

for (int i = 0; i < 100; i++) {
EXPECT_NO_THROW(first.pop()) << "Исключение";
}
ASSERT_ANY_THROW(first.pop()) << "Нет исключения";
}


TEST(Top, PushIn) {
Stack<int> first;

EXPECT_ANY_THROW(first.top()) << "Нет исключения";

first.push(123);
EXPECT_EQ(first.top(), 123) << first.top() << " " << 123;

first.push(-321);
EXPECT_EQ(first.top(), -321) << first.top() << " " << -321;

first.push(5555);
EXPECT_EQ(first.top(), 5555) << first.top() << " " << 5555;

}

TEST(Copy_ctr, Eq) {
Stack<int> first;
first.push(123);
first.push(123);
Stack<int> second;
EXPECT_NO_THROW(second = first) << "Исключение";
}

TEST(Copy_ctr, Constructor) {
Stack<int> first;
first.push(123);
first.push(123);
EXPECT_NO_THROW(Stack<int> second = first) << "Исключение";
}

TEST(Move_ctr, Eq) {
Stack<int> first;
first.push(123);
first.push(123);
Stack<int> second;
EXPECT_NO_THROW(second = std::move(first)) << "Исключение";
}

TEST(Move_ctr, Constructor) {
Stack<int> first;
first.push(123);
first.push(123);
EXPECT_NO_THROW(Stack<int> second = std::move(first)) << "Исключение";
}