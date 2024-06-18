// test_example.cpp
#include "gtest/gtest.h"
#include "test_functions.h"

TEST(ExampleTest, AddsTwoNumbers) {
    EXPECT_EQ(3, add(1, 2));
}