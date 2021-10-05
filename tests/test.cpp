// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include <iostream>
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

TEST(SharedPtr, test3) {
    int *a = new int[1];
    a[0] = 5;
    SharedPtr<int> A(a);
    SharedPtr<int> B;
    B = std::move(A);
    EXPECT_EQ(A.use_count(), 0);
    EXPECT_EQ(B.use_count(), 1);
    EXPECT_EQ(*B, 5);
    EXPECT_FALSE(A);
}

TEST(SharedPtr, test4) {
    int *a = new int[1];
    a[0] = 5;
    SharedPtr<int> A(a);
    SharedPtr<int> B = A;
    EXPECT_EQ(A.use_count(), 2);
    EXPECT_EQ(A.get()[0], 5);
    EXPECT_EQ(B.use_count(), 2);
    EXPECT_EQ(B.get()[0], 5);
}

TEST(SharedPtr, test5) {
    int *a = new int[1];
    a[0] = 5;
    int *b = new int[1];
    b[0] = 3;
    SharedPtr<int> A(a);
    SharedPtr<int> B(b);
    A.swap(B);
    EXPECT_EQ(*A, 3);
    EXPECT_EQ(*B, 5);
}

TEST(SharedPtr, test6) {
    int *a = new int[1];
    a[0] = 5;
    int *b = new int[1];
    b[0] = 3;
    SharedPtr<int> A(a);
    SharedPtr<int> B(b);
    A.reset();
    EXPECT_EQ(A.use_count(), 0);
    EXPECT_EQ(B.use_count(), 1);
    A.reset(b);
    EXPECT_EQ(*A, 3);
    EXPECT_EQ(*B, 3);
    EXPECT_EQ(A.use_count(), 2);
    EXPECT_EQ(B.use_count(), 2);
}

TEST(SharedPtr, test7) {
    class phone {

    private:

    public:
        phone(int n){
            this->number = n;
        }
        int number;
    };

    phone* a = new phone(123);
    SharedPtr<phone> A(a);
    EXPECT_EQ(A->number, 123);
}
