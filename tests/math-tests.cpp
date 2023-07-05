/**
 * @file math-tests.cpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief This file contains the tests for the math library.
 * @version 1.0
 * @date 2023-07-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <gtest/gtest.h>

#include "math.hpp"

class MathTests : public ::testing::Test {
 public:
  MathTests() {}
  virtual ~MathTests() {}

  virtual void SetUp() override {}
  virtual void TearDown() override {}
};

TEST(MathTests, CreateMatrix) {
  custom_math::Matrix *matrix = custom_math::matrix_create(2, 2);
  EXPECT_EQ(matrix->rows, 2);
  EXPECT_EQ(matrix->cols, 2);
  custom_math::matrix_delete(matrix);
}

TEST(MathTests, CreateMatrixIncorrect) {
  custom_math::Matrix *matrix = custom_math::matrix_create(-1, 2);
  EXPECT_EQ(matrix, nullptr);
}

TEST(MathTests, DeleteMatrix) {
  custom_math::Matrix *matrix = custom_math::matrix_create(2, 2);
  custom_math::matrix_delete(matrix);

  EXPECT_EQ(matrix->elements, nullptr);
}

TEST(MathTests, IMatrix) {
  custom_math::Matrix *matrix = custom_math::matrix_I(2);

  EXPECT_EQ(matrix->elements[0], 1);
  EXPECT_EQ(matrix->elements[1], 0);
  EXPECT_EQ(matrix->elements[2], 0);
  EXPECT_EQ(matrix->elements[3], 1);

  custom_math::matrix_delete(matrix);
}

TEST(MathTests, CopyMatrix) {
  custom_math::Matrix *matrix = custom_math::matrix_create(2, 2);
  matrix->elements[0] = 1;
  matrix->elements[1] = 2;
  matrix->elements[2] = 3;
  matrix->elements[3] = 4;

  custom_math::Matrix *new_matrix = custom_math::matrix_copy(matrix);

  EXPECT_EQ(new_matrix->elements[0], 1);
  EXPECT_EQ(new_matrix->elements[1], 2);
  EXPECT_EQ(new_matrix->elements[2], 3);
  EXPECT_EQ(new_matrix->elements[3], 4);

  custom_math::matrix_delete(matrix);
  custom_math::matrix_delete(new_matrix);
}

TEST(MathTests, AddMatrix) {
  custom_math::Matrix *matrix1 = custom_math::matrix_create(2, 2);
  matrix1->elements[0] = 1;
  matrix1->elements[1] = 2;
  matrix1->elements[2] = 3;
  matrix1->elements[3] = 4;

  custom_math::Matrix *matrix2 = custom_math::matrix_create(2, 2);
  matrix2->elements[0] = 7;
  matrix2->elements[1] = 8;
  matrix2->elements[2] = 9;
  matrix2->elements[3] = 0;

  custom_math::Matrix *matrix3 = custom_math::matrix_add(matrix1, matrix2);
  EXPECT_EQ(matrix3->elements[0], 8);
  EXPECT_EQ(matrix3->elements[1], 10);
  EXPECT_EQ(matrix3->elements[2], 12);
  EXPECT_EQ(matrix3->elements[3], 4);

  custom_math::matrix_delete(matrix1);
  custom_math::matrix_delete(matrix2);
  custom_math::matrix_delete(matrix3);
}

TEST(MathTests, AddMatrixIncorrect) {
  custom_math::Matrix *matrix1 = custom_math::matrix_create(2, 3);
  matrix1->elements[0] = 1;
  matrix1->elements[1] = 2;
  matrix1->elements[2] = 3;
  matrix1->elements[3] = 4;
  matrix1->elements[4] = 5;
  matrix1->elements[5] = 6;

  custom_math::Matrix *matrix2 = custom_math::matrix_create(2, 2);
  matrix2->elements[0] = 7;
  matrix2->elements[1] = 8;
  matrix2->elements[2] = 9;
  matrix2->elements[3] = 0;

  custom_math::Matrix *matrix3 = custom_math::matrix_add(matrix1, matrix2);
  EXPECT_EQ(matrix3, nullptr);

  custom_math::matrix_delete(matrix1);
  custom_math::matrix_delete(matrix2);
}

TEST(MathTests, SubtractMatrix) {
  custom_math::Matrix *matrix1 = custom_math::matrix_create(2, 2);
  matrix1->elements[0] = 1;
  matrix1->elements[1] = 1;
  matrix1->elements[2] = 1;
  matrix1->elements[3] = 1;

  custom_math::Matrix *matrix2 = custom_math::matrix_create(2, 2);
  matrix2->elements[0] = 7;
  matrix2->elements[1] = 8;
  matrix2->elements[2] = 9;
  matrix2->elements[3] = 0;

  custom_math::Matrix *matrix3 = custom_math::matrix_sub(matrix1, matrix2);
  EXPECT_EQ(matrix3->elements[0], -6);
  EXPECT_EQ(matrix3->elements[1], -7);
  EXPECT_EQ(matrix3->elements[2], -8);
  EXPECT_EQ(matrix3->elements[3], 1);

  custom_math::matrix_delete(matrix1);
  custom_math::matrix_delete(matrix2);
  custom_math::matrix_delete(matrix3);
}

TEST(MathTests, SubtractMatrixIncorrect) {
  custom_math::Matrix *matrix1 = custom_math::matrix_create(2, 3);
  matrix1->elements[0] = 1;
  matrix1->elements[1] = 1;
  matrix1->elements[2] = 1;
  matrix1->elements[3] = 1;
  matrix1->elements[4] = 1;
  matrix1->elements[5] = 1;

  custom_math::Matrix *matrix2 = custom_math::matrix_create(2, 2);
  matrix2->elements[0] = 7;
  matrix2->elements[1] = 8;
  matrix2->elements[2] = 9;
  matrix2->elements[3] = 0;

  custom_math::Matrix *matrix3 = custom_math::matrix_sub(matrix1, matrix2);
  EXPECT_EQ(matrix3, nullptr);

  custom_math::matrix_delete(matrix1);
  custom_math::matrix_delete(matrix2);
}

TEST(MathTests, DotMatrix) {
  custom_math::Matrix *matrix1 = custom_math::matrix_create(2, 2);
  matrix1->elements[0] = 1;
  matrix1->elements[1] = 3;
  matrix1->elements[2] = 2;
  matrix1->elements[3] = 4;

  custom_math::Matrix *matrix2 = custom_math::matrix_create(2, 2);
  matrix2->elements[0] = 7;
  matrix2->elements[1] = 8;
  matrix2->elements[2] = 9;
  matrix2->elements[3] = 0;

  custom_math::Matrix *matrix3 = custom_math::matrix_dot(matrix1, matrix2);
  EXPECT_EQ(matrix3->elements[0], 34);
  EXPECT_EQ(matrix3->elements[1], 8);
  EXPECT_EQ(matrix3->elements[2], 50);
  EXPECT_EQ(matrix3->elements[3], 16);

  custom_math::matrix_delete(matrix1);
  custom_math::matrix_delete(matrix2);
  custom_math::matrix_delete(matrix3);
}

TEST(MathTests, DotMatrixDifferentSizes) {
  custom_math::Matrix *matrix1 = custom_math::matrix_create(3, 2);
  matrix1->elements[0] = 1;
  matrix1->elements[1] = 3;
  matrix1->elements[2] = 2;
  matrix1->elements[3] = 4;
  matrix1->elements[4] = 5;
  matrix1->elements[5] = 6;

  custom_math::Matrix *matrix2 = custom_math::matrix_create(2, 3);
  matrix2->elements[0] = 7;
  matrix2->elements[1] = 8;
  matrix2->elements[2] = 9;
  matrix2->elements[3] = 0;
  matrix2->elements[4] = 1;
  matrix2->elements[5] = 2;

  custom_math::Matrix *matrix3 = custom_math::matrix_dot(matrix1, matrix2);
  EXPECT_EQ(matrix3->cols, 3);
  EXPECT_EQ(matrix3->rows, 3);
  EXPECT_EQ(matrix3->elements[0], 7);
  EXPECT_EQ(matrix3->elements[1], 11);
  EXPECT_EQ(matrix3->elements[2], 15);
  EXPECT_EQ(matrix3->elements[3], 14);
  EXPECT_EQ(matrix3->elements[4], 20);
  EXPECT_EQ(matrix3->elements[5], 26);
  EXPECT_EQ(matrix3->elements[6], 35);
  EXPECT_EQ(matrix3->elements[7], 46);
  EXPECT_EQ(matrix3->elements[8], 57);

  custom_math::matrix_delete(matrix1);
  custom_math::matrix_delete(matrix2);
  custom_math::matrix_delete(matrix3);
}

TEST(MathTests, DotMatrixIncorrect) {
  custom_math::Matrix *matrix1 = custom_math::matrix_create(2, 1);
  matrix1->elements[0] = 1;
  matrix1->elements[1] = 3;

  custom_math::Matrix *matrix2 = custom_math::matrix_create(2, 2);
  matrix2->elements[0] = 7;
  matrix2->elements[1] = 8;
  matrix2->elements[2] = 9;
  matrix2->elements[3] = 0;

  custom_math::Matrix *matrix3 = custom_math::matrix_dot(matrix1, matrix2);
  EXPECT_EQ(matrix3, nullptr);

  custom_math::matrix_delete(matrix1);
  custom_math::matrix_delete(matrix2);
}

TEST(MathTests, ScalarMatrix) {
  custom_math::Matrix *matrix = custom_math::matrix_create(2, 2);
  matrix->elements[0] = 7;
  matrix->elements[1] = 8;
  matrix->elements[2] = 9;
  matrix->elements[3] = 0;

  custom_math::Matrix *matrix2 = custom_math::matrix_mul_scalar(matrix, 2);

  EXPECT_EQ(matrix2->elements[0], 14);
  EXPECT_EQ(matrix2->elements[1], 16);
  EXPECT_EQ(matrix2->elements[2], 18);
  EXPECT_EQ(matrix2->elements[3], 0);

  custom_math::matrix_delete(matrix);
  custom_math::matrix_delete(matrix2);
}

TEST(MathTests, TransposeMatrix) {
  custom_math::Matrix *matrix = custom_math::matrix_create(2, 2);
  matrix->elements[0] = 7;
  matrix->elements[1] = 8;
  matrix->elements[2] = 9;
  matrix->elements[3] = 0;

  custom_math::Matrix *matrix2 = custom_math::matrix_transpose(matrix);
  EXPECT_EQ(matrix2->elements[0], 7);
  EXPECT_EQ(matrix2->elements[1], 9);
  EXPECT_EQ(matrix2->elements[2], 8);
  EXPECT_EQ(matrix2->elements[3], 0);

  custom_math::matrix_delete(matrix);
  custom_math::matrix_delete(matrix2);
}

TEST(MathTests, TransposeMatrixIncorrect) {
  custom_math::Matrix *matrix = custom_math::matrix_transpose(nullptr);

  EXPECT_EQ(matrix, nullptr);
}

TEST(MathTests, DeterminantMatrix) {
  custom_math::Matrix *matrix = custom_math::matrix_create(4, 4);
  matrix->elements[0] = 7;
  matrix->elements[1] = 8;
  matrix->elements[2] = 9;
  matrix->elements[3] = 0;
  matrix->elements[4] = 1;
  matrix->elements[5] = 2;
  matrix->elements[6] = 3;
  matrix->elements[7] = 4;
  matrix->elements[8] = 5;
  matrix->elements[9] = 6;
  matrix->elements[10] = 7;
  matrix->elements[11] = 8;
  matrix->elements[12] = 9;
  matrix->elements[13] = 3;
  matrix->elements[14] = 4;
  matrix->elements[15] = 2;

  double determinant = custom_math::matrix_determinant(matrix);
  EXPECT_EQ(determinant, -280);

  custom_math::matrix_delete(matrix);
}

TEST(MathTests, ApplyFunctionToMatrix) {
  custom_math::Matrix *matrix = custom_math::matrix_create(2, 2);
  matrix->elements[0] = 7;
  matrix->elements[1] = 8;
  matrix->elements[2] = 9;
  matrix->elements[3] = 0;

  custom_math::Matrix *matrix2 =
      custom_math::matrix_apply(matrix, [](double x) { return x * 2; });
  EXPECT_EQ(matrix2->elements[0], 14);
  EXPECT_EQ(matrix2->elements[1], 16);
  EXPECT_EQ(matrix2->elements[2], 18);
  EXPECT_EQ(matrix2->elements[3], 0);

  custom_math::matrix_delete(matrix);
  custom_math::matrix_delete(matrix2);
}
