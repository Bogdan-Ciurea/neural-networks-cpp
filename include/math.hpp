/**
 * @file math.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief This file is the header file for the math library that contains the
 *       math functions that are used in the project.
 * @version 1.0
 * @date 2023-07-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef MATH_HPP_
#define MATH_HPP_

#include <stdio.h>

namespace custom_math {

typedef struct {
  int rows, cols;
  double *elements;
} Matrix;

/**
 * @brief This function is used to create a matrix.
 *
 * @param rows The number of rows of the matrix.
 * @param cols The number of columns of the matrix.
 *
 * @return Matrix The matrix that was created.
 */
Matrix create_matrix(int rows, int cols);

/**
 * @brief This function is used to delete a matrix.
 *
 * @param matrix The matrix that will be deleted.
 */
void delete_matrix(Matrix matrix);

/**
 * @brief This function is used to print a matrix.
 *
 * @param matrix The matrix that will be printed.
 */
void print_matrix(Matrix matrix);
};  // namespace custom_math

#endif  // MATH_HPP_