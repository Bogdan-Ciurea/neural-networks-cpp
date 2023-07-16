/**
 * @file image-tests.cpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief  This file contains the tests for the functions declared in image.hpp.
 * @version 1.0
 * @date 2023-07-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <gtest/gtest.h>

#include "image.hpp"

class ImageTests : public ::testing::Test {
 public:
  ImageTests() {}
  virtual ~ImageTests() {}

  virtual void SetUp() override {}
  virtual void TearDown() override {}
};

TEST(ImageTests, ReadTestFile) {
  images::Image **images = images::read_test_images();

  EXPECT_NE(images, nullptr);
  int i;

#ifdef USE_OPENMP
#pragma omp parallel for private(i)
#endif
  for (i = 0; i < 10000; i++) {
    EXPECT_NE(images[i], nullptr);
    EXPECT_NE(images[i]->pixels, nullptr);
    EXPECT_EQ(images[i]->pixels->rows, 28);
    EXPECT_EQ(images[i]->pixels->cols, 28);
  }
}

TEST(ImageTests, ReadTrainFile) {
  images::Image **images = images::read_train_images();

  EXPECT_NE(images, nullptr);
  int i;

#ifdef USE_OPENMP
#pragma omp parallel for private(i)
#endif
  for (i = 0; i < 60000; i++) {
    EXPECT_NE(images[i], nullptr);
    EXPECT_NE(images[i]->pixels, nullptr);
    EXPECT_EQ(images[i]->pixels->rows, 28);
    EXPECT_EQ(images[i]->pixels->cols, 28);
  }
}