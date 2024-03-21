#include <gtest>
#include <exception>
#include <string>

#include "mystack.h"
using namespace myStack;

TEST(push, PushIn) {
Stack<int> first;

EXPECT_NO_THROW(first.Push(123)) << "Исключение";
EXPECT_NO_THROW(first.Push(23)) << "Исключение";
EXPECT_NO_THROW(first.Push(12300)) << "Исключение";
EXPECT_NO_THROW(first.Push(123000)) << "Исключение";

for (int i = 0; i < 100; i++) {
EXPECT_NO_THROW(first.Push(123000)) << "Исключение";
}

}

TEST(Pop, PopOut) {
Stack<int> first;

for (int i = 0; i < 100; i++) {
first.Push(123);
}

for (int i = 0; i < 100; i++) {
EXPECT_NO_THROW(first.Pop()) << "Исключение";
}
ASSERT_ANY_THROW(first.Pop()) << "Нет исключения";
}


TEST(Top, PushIn) {
Stack<int> first;

EXPECT_ANY_THROW(first.Top()) << "Нет исключения";

first.Push(123);
EXPECT_EQ(first.Top(), 123) << first.Top() << " " << 123;

first.Push(-123);
EXPECT_EQ(first.Top(), -123) << first.Top() << " " << -123;

first.Push(111);
EXPECT_EQ(first.Top(), 111) << first.Top() << " " << 111;

}

TEST(IsEmpty, IsEmpty) {
Stack<int> first;

EXPECT_EQ(first.IsEmpty(), true) << first.IsEmpty() << " " << true;

first.Push(123);
EXPECT_EQ(first.IsEmpty(), false) << first.IsEmpty() << " " << true;

first.Pop();
EXPECT_EQ(first.IsEmpty(), true) << first.IsEmpty() << " " << true;

}
