#include "pch.h"
#include "../watchtower-production/src/test_functions.cpp"

TEST(myFunctionsTest, addTest) {
  // Test case: Check if add() function correctly adds two numbers
  double result = add(1, 2);
  EXPECT_EQ(result, 3);
}