/**
 * @file math.cpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief This file is the source file for the math library that contains the
 *      math functions that are used in the project.
 * @version 1.0
 * @date 2023-07-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "math.hpp"

namespace custom_math {

Matrix create_matrix(int rows, int cols) {
  Matrix matrix;
  matrix.rows = rows;
  matrix.cols = cols;
  matrix.elements = new double[rows * cols];
  return matrix;
}

void delete_matrix(Matrix matrix) { delete[] matrix.elements; }

void print_matrix(Matrix matrix) {
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.cols; j++) {
      printf("%f ", matrix.elements[i * matrix.cols + j]);
    }
    printf("\n");
  }
}

}  // namespace custom_math