#include <gtest/gtest.h>
#include <exception>
#include <string>

#include "mystack.h"
using namespace myStack;

TEST(Push, PushIn) {
    Stack<int> first;

    EXPECT_NO_THROW(first.push(1)) << "Исключение";
    EXPECT_NO_THROW(first.push(2)) << "Исключение";
    EXPECT_NO_THROW(first.push(3)) << "Исключение";
    EXPECT_NO_THROW(first.push(100)) << "Исключение";

    for (int i = 0; i < 100; i++) {
        EXPECT_NO_THROW(first.push(100000)) << "Исключение";
    }

}

TEST(Pop, PopOut) {
    Stack<int> first;

    for (int i = 0; i < 100; i++) {
        first.push(11111);
    }

    for (int i = 0; i < 100; i++) {
        EXPECT_NO_THROW(first.pop()) << "Исключение";
    }
    ASSERT_ANY_THROW(first.pop()) << "Нет исключения";
}


TEST(Top, PushIn) {
    Stack<int> first;

    EXPECT_ANY_THROW(first.top()) << "Нет исключения";

    first.push(1);
    EXPECT_EQ(first.top(), 1) << first.top() << " " << 1;

    first.push(-1);
    EXPECT_EQ(first.top(), -1) << first.top() << " " << -1;
}

TEST(Copy_ctr, Eq) {
    Stack<int> first;
    first.push(1);
    first.push(1);
    Stack<int> second;
    EXPECT_NO_THROW(second = first) << "Исключение";
}

TEST(Copy_ctr, Constructor) {
    Stack<int> first;
    first.push(1);
    first.push(1);
    EXPECT_NO_THROW(Stack<int> second = first) << "Исключение";
}

TEST(Move_ctr, Eq) {
    Stack<int> first;
    first.push(1);
    first.push(1);
    Stack<int> second;
    EXPECT_NO_THROW(second = std::move(first)) << "Исключение";
}

TEST(Move_ctr, Constructor) {
    Stack<int> first;
    first.push(1);
    first.push(1);
    EXPECT_NO_THROW(Stack<int> second = std::move(first)) << "Исключение";
}