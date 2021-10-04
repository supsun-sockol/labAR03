// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include "../include/header.hpp"

TEST(Example, EmptyTest) {
    EXPECT_TRUE(true);
}

TEST(SharedPtr, test1) {
    SharedPtr<int> A;
    EXPECT_EQ(A.use_count(), 0);
    EXPECT_FALSE(A);
}
TEST(SharedPtr, test2) {
    int *a = new int[1];
    a[0] = 5;
    SharedPtr<int> A(a);
    EXPECT_EQ(A.use_count(), 1);
    EXPECT_EQ(*A, 5);
}
