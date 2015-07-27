#include <limits.h>
#include "factorial.h"
// You should include this header file to use gtest for C++
#include "gtest/gtest.h"

// The first test is to check the factorial() function should return
// a positive value---maybe 1--- with a negiative integer parameter.
TEST (factorialTest, NegativeInput) {
    EXPECT_EQ(1, factorial(-5));    // factorial(-5) should be 1
    EXPECT_EQ(1, factorial(-1));    // factorial(-1) should be 1
    EXPECT_GT(factorial(-10), 0);   // factorial(-10) should be greater than 0
}

// The second test is to check the return value of factorial(0) should be 1.
TEST (factorialTest, ZeroInput) { 
    EXPECT_EQ(1, factorial(0));     // factorial(0) should be 1
}

// The third test is to check the factorial() function should return
// a correct fatorial value with a positive integer parameter. 
TEST (factorialTest, PositiveInput) {
    EXPECT_EQ(1, factorial(1));     // factorial(1) should be 1
    EXPECT_EQ(2, factorial(2));     // factorial(2) should be 2
    EXPECT_EQ(6, factorial(3));     // factorial(6) should be 6
    EXPECT_EQ(40320, factorial(8)); // factorial(8) should be 40320
}
