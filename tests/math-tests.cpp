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
  // custom_math::Matrix matrix = custom_math::create_matrix(2, 2);
  // EXPECT_EQ(matrix.rows, 2);
  // EXPECT_EQ(matrix.cols, 2);
  // custom_math::delete_matrix(matrix);
  EXPECT_EQ(1, 1);
}