// test_example.cpp
#include "gtest/gtest.h"
#include "example.h"

TEST(ExampleTest, AddsTwoNumbers) {
    EXPECT_EQ(3, add(1, 2));
}

TEST(ExampleTest, AddsTwoNegativeNumbers) {
    EXPECT_EQ(-3, add(-1, -2));
}