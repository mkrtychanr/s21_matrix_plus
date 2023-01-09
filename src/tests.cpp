#include <iostream>
#include <cstdio>
#include "s21_matrix_oop.h"
#include <gtest/gtest.h>

void printMatrix(S21Matrix& m) {
    for (int i = 0; i < m.GetRows(); i++) {
        for (int j = 0; j < m.GetCols(); j++) {
            std::cout<<m(i, j)<<" ";
        }
        std::cout<<std::endl;
    }
}

namespace {
    TEST(Constructor, Default) {
        auto test = S21Matrix();
        EXPECT_EQ(test.GetRows(), 0);
        EXPECT_EQ(test.GetCols(), 0);
    }

    TEST(Constructor, By2Args) {
        auto test = S21Matrix(3, 3);
        EXPECT_EQ(test.GetRows(), 3);
        EXPECT_EQ(test.GetCols(), 3);
    }

    TEST(Constructor, Copy) {
        auto test = S21Matrix(3, 3);
        test(0,0) = 1;
        auto temp = S21Matrix(test);
        EXPECT_EQ(test, temp);
    }

    TEST(Constructor, Move) {
        auto test1 = S21Matrix(3, 3);
        test1(1, 1) = 5;
        auto test2 = S21Matrix(test1);
        auto test3 = S21Matrix(std::move(test1));
        EXPECT_EQ(test2, test3);
    }

    TEST(SimpleMathOperations, EqMatrix) {
        auto test1 = S21Matrix(3, 3);
        test1(1,2) = 5;
        auto test2 = test1;
        EXPECT_TRUE(test1.EqMatrix(test2));
        EXPECT_TRUE(test1.EqMatrix(test2) == (test1 == test2));
        test2(1, 1) = 1;
        EXPECT_FALSE(test1.EqMatrix(test2));
        EXPECT_TRUE(test1.EqMatrix(test2) == (test1 == test2));
        auto test3 = S21Matrix(5, 5);
        EXPECT_FALSE(test1.EqMatrix(test3));
        EXPECT_TRUE(test1.EqMatrix(test3) == (test1 == test3));
    }

    TEST(SimpleMathOperations, SumMatrix) {
        auto test1 = S21Matrix(1, 1);
        test1(0, 0) = 1;
        auto test2 = test1;
        test1.SumMatrix(test2);
        EXPECT_EQ(test1(0, 0), 2);
    }

    TEST(SimpleMathOperations, SubMatrix) {
        auto test1 = S21Matrix(1, 1);
        test1(0, 0) = 1;
        auto test2 = test1;
        test1.SubMatrix(test2);
        EXPECT_EQ(test1(0, 0), 0);
    }

    TEST(SimpleMathOperations, MulNumber) {
        auto test1 = S21Matrix(1, 1);
        test1(0, 0) = 5;
        test1.MulNumber(3);
        EXPECT_EQ(test1(0, 0), 15);
    }

    TEST(SimpleMathOperations, MulMatrix) {
        auto test1 = S21Matrix(3, 3);
        for (int i = 0; i < test1.GetRows(); i++) {
            for (int j = 0; j < test1.GetCols(); j++) {
                test1(i, j) = test1.GetRows() * i + j + 1;
            }
        }
        auto test2 = test1;
        test1.MulMatrix(test2);
        test2(0, 0) = 30;
        test2(0, 1) = 36;
        test2(0, 2) = 42;
        test2(1, 0) = 66;
        test2(1, 1) = 81;
        test2(1, 2) = 96;
        test2(2, 0) = 102;
        test2(2, 1) = 126;
        test2(2, 2) = 150;
        EXPECT_EQ(test1, test2);
    }

    TEST(LinearOperations, Transpose) {
        auto test1 = S21Matrix(3, 3);
        for (int i = 0; i < test1.GetRows(); i++) {
            for (int j = 0; j < test1.GetCols(); j++) {
                test1(i, j) = test1.GetRows() * i + j + 1;
            }
        }
        test1 = test1.Transpose();
        auto test2 = S21Matrix(3, 3);
        test2(0, 0) = 1;
        test2(0, 1) = 4;
        test2(0, 2) = 7;
        test2(1, 0) = 2;
        test2(1, 1) = 5;
        test2(1, 2) = 8;
        test2(2, 0) = 3;
        test2(2, 1) = 6;
        test2(2, 2) = 9;
        EXPECT_EQ(test1, test2);
    }

    TEST(LinearOperations, CalcComplements) {
        auto test1 = S21Matrix(3, 3);
        test1(0, 0) = 1;
        test1(0, 1) = 2;
        test1(0, 2) = 3;
        test1(1, 0) = 0;
        test1(1, 1) = 4;
        test1(1, 2) = 2;
        test1(2, 0) = 5;
        test1(2, 1) = 2;
        test1(2, 2) = 1;
        test1 = test1.CalcComplements();
        auto test2 = S21Matrix(3, 3);
        test2(0, 0) = 0;
        test2(0, 1) = 10;
        test2(0, 2) = -20;
        test2(1, 0) = 4;
        test2(1, 1) = -14;
        test2(1, 2) = 8;
        test2(2, 0) = -8;
        test2(2, 1) = -2;
        test2(2, 2) = 4;
        EXPECT_EQ(test1, test2);
    }

    TEST(LinearOperations, Determinant) {
        auto test1 = S21Matrix(3, 3);
        test1(0, 0) = 1;
        test1(0, 1) = 2;
        test1(0, 2) = 3;
        test1(1, 0) = 0;
        test1(1, 1) = 4;
        test1(1, 2) = 2;
        test1(2, 0) = 5;
        test1(2, 1) = 2;
        test1(2, 2) = 1;
        EXPECT_DOUBLE_EQ(test1.Determinant(), -40);
    }

    TEST(LinearOperations, InverseMatrix) {
        auto test1 = S21Matrix(3, 3);
        test1(0, 0) = 2;
        test1(0, 1) = 5;
        test1(0, 2) = 7;
        test1(1, 0) = 6;
        test1(1, 1) = 3;
        test1(1, 2) = 4;
        test1(2, 0) = 5;
        test1(2, 1) = -2;
        test1(2, 2) = -3;
        test1 = test1.InverseMatrix();
        auto test2 = S21Matrix(3, 3);
        test2(0, 0) = 1;
        test2(0, 1) = -1;
        test2(0, 2) = 1;
        test2(1, 0) = -38;
        test2(1, 1) = 41;
        test2(1, 2) = -34;
        test2(2, 0) = 27;
        test2(2, 1) = -29;
        test2(2, 2) = 24;
        EXPECT_EQ(test1, test2);
    }

    TEST(Technical, GetRows) {
        auto test1 = S21Matrix();
        EXPECT_EQ(test1.GetRows(), 0);
        auto test2 = S21Matrix(2, 2);
        EXPECT_EQ(test2.GetRows(), 2);
    }

    TEST(Technical, GetCols) {
        auto test1 = S21Matrix();
        EXPECT_EQ(test1.GetCols(), 0);
        auto test2 = S21Matrix(2, 2);
        EXPECT_EQ(test2.GetCols(), 2);
    }

    TEST(Technical, SetRows) {
        auto test1 = S21Matrix(1, 1);
        test1.SetRows(5);
        EXPECT_EQ(test1.GetRows(), 5);
        test1.SetRows(1);
    }

    TEST(Technical, SetCols) {
        auto test1 = S21Matrix(1, 1);
        test1.SetCols(5);
        EXPECT_EQ(test1.GetCols(), 5);
        test1.SetRows(1);
    }
}
