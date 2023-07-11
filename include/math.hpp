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

#ifdef USE_OPENMP
  #define HAVE_OPENMP true
  #include <omp.h>
#else
  #define HAVE_OPENMP false
#endif
#include <stdio.h>
#include <stdlib.h>

namespace custom_math {

typedef struct {
  size_t rows, cols;
  double *elements;
} Matrix;

/**
 * @brief This function is used to create a matrix.
 *
 * @param rows The number of rows of the matrix.
 * @param cols The number of columns of the matrix.
 * @param value The value of each element of the matrix.
 *
 * @return Matrix* The matrix that was created.
 */
Matrix *matrix_create(const int rows,const  int cols, const double value = 0.0);


/**
 * @brief This function is used to create an identity matrix.
 *
 * @param size     The size of the matrix.
 * @return Matrix* The identity matrix.
 */
Matrix *matrix_I(const int size);

/**
 * @brief This function is used to delete a matrix.
 *
 * @param matrix* The matrix that will be deleted.
 */
void matrix_delete(Matrix *matrix);

/**
 * @brief This function is used to print a matrix.
 *
 * @param matrix* The matrix that will be printed.
 */
void matrix_print(const Matrix *matrix);

/**
 * @brief This function is used to copy a matrix.
 *
 * @param matrix*   The matrix that will be copied.
 * @return Matrix* The copy of the matrix.
 */
Matrix *matrix_copy(const Matrix *matrix);

void matrix_save(Matrix *matrix, const char *filename);

Matrix *matrix_load(const char *filename);

// Operations on matrices

/**
 * @brief This function is used to add two matrices.
 *
 * @param matrix1*   The first matrix.
 * @param matrix2*   The second matrix.
 * @return Matrix*  The sum of the two matrices.
 */
Matrix *matrix_add(Matrix *matrix1, Matrix *matrix2);

/**
 * @brief This function is used to subtract two matrices.
 *
 * @param matrix1*   The first matrix.
 * @param matrix2*   The second matrix.
 * @return Matrix*  The difference of the two matrices.
 */
Matrix *matrix_sub(Matrix *matrix1, Matrix *matrix2);

/**
 * @brief This function is used to multiply two matrices.
 *
 * @param matrix1*   The first matrix.
 * @param matrix2*   The second matrix.
 * @return Matrix*  The product of the two matrices.
 */
Matrix *matrix_dot(Matrix *matrix1, Matrix *matrix2);

/**
 * @brief This function is used to multiply a matrix with a scalar.
 *
 * @param matrix*    The matrix.
 * @param scalar    The scalar.
 * @return Matrix*  The product of the matrix and the scalar.
 */
Matrix *matrix_mul_scalar(Matrix *matrix, double scalar);

/**
 * @brief  This is used to transpose a matrix.
 *
 * @param matrix*  The matrix.
 * @return Matrix* The transpose of the matrix.
 */
Matrix *matrix_transpose(Matrix *matrix);

Matrix *matrix_minor(Matrix *matrix, int row, int col);

/**
 * @brief This function is used to calculate the determinant of a matrix.
 *
 * @param matrix*  The matrix.
 * @return Matrix* The determinant of the matrix.
 */
double matrix_determinant(Matrix *matrix);

/**
 * @brief This function is used to calculate the inverse of a matrix.
 *
 * @param matrix*  The matrix.
 * @param function The function that will be applied to the matrix.
 * @return Matrix* The resulted of the matrix.
 */
Matrix *matrix_apply(Matrix *matrix, double (*function)(double));

};  // namespace custom_math

#endif  // MATH_HPP_