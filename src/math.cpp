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

Matrix *matrix_create(const int rows, const int cols, const double value) {
  if (rows <= 0 || cols <= 0) return nullptr;

  Matrix *matrix = new Matrix;

  if (matrix == nullptr) return nullptr;

  matrix->rows = rows;
  matrix->cols = cols;
  matrix->elements = new double[rows * cols];

  if (matrix->elements == nullptr) {
    delete matrix;
    matrix = nullptr;
  }

  // Initialize the matrix with the given value.
  #ifndef __APPLE__ AND value == 0 // Apparently, Apple M1 will initialize the matrix with 0.
    int i;
    #ifdef USE_OPENMP
    #pragma omp parallel for private(i)
    #endif
    for (i = 0; i < rows * cols; i++) matrix->elements[i] = value;
  #endif

  return matrix;
}

Matrix *matrix_I(const int size) {
  Matrix *matrix = matrix_create(size, size);
  int i, j;

  #ifdef USE_OPENMP
  #pragma omp parallel for private(i, j)
  #endif
  for (i = 0; i < size; i++)
    for (j = 0; j < size; j++)
      matrix->elements[i * size + j] = (i == j) ? 1. : 0.;

  return matrix;
}

void matrix_delete(Matrix *matrix) {
  if (matrix == nullptr) return;

  delete[] matrix->elements;
  matrix->elements = nullptr;
  delete matrix;
  matrix = nullptr;
}

void matrix_print(const Matrix *matrix) {
  if (matrix == nullptr || matrix->elements == nullptr) return;

  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->cols; j++) {
      printf("%f ", matrix->elements[i * matrix->cols + j]);
    }
    printf("\n");
  }
}

Matrix *matrix_copy(const Matrix *matrix) {
  if (matrix == nullptr || matrix->elements == nullptr) return nullptr;

  Matrix *new_matrix = matrix_create(matrix->rows, matrix->cols);
  int i, j;

  #ifdef USE_OPENMP
  #pragma omp parallel for private(i, j) shared(matrix, new_matrix)
  #endif
  for (i = 0; i < matrix->rows; i++)
    for (j = 0; j < matrix->cols; j++)
      new_matrix->elements[i * matrix->cols + j] =
          matrix->elements[i * matrix->cols + j];

  return new_matrix;
}

void matrix_save(Matrix *matrix, const char *filename) {
  FILE *file = fopen(filename, "w");

  fprintf(file, "%ld %ld\n", matrix->rows, matrix->cols);

  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->cols; j++) {
      fprintf(file, "%f ", matrix->elements[i * matrix->cols + j]);
    }
    fprintf(file, "\n");
  }

  fclose(file);
}

Matrix *matrix_load(const char *filename) {
  FILE *file = fopen(filename, "r");

  size_t rows, cols;
  fscanf(file, "%ld %ld", &rows, &cols);

  Matrix *matrix = matrix_create(rows, cols);

  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->cols; j++) {
      fscanf(file, "%lf", &matrix->elements[i * matrix->cols + j]);
    }
  }

  fclose(file);

  return matrix;
}

Matrix *matrix_add(Matrix *matrix1, Matrix *matrix2) {
  if (matrix1 == nullptr || matrix1->elements == nullptr ||
      matrix2 == nullptr || matrix2->elements == nullptr)
    return nullptr;

  if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols)
    return nullptr;

  Matrix *matrix = matrix_create(matrix1->rows, matrix1->cols);
  int i, j;

  #if HAVE_OPENMP
  #pragma omp parallel for private(i, j) shared(matrix1, matrix2, matrix)
  #endif
  for (i = 0; i < matrix1->rows; i++)
    for (j = 0; j < matrix1->cols; j++)
      matrix->elements[i * matrix1->cols + j] =
          matrix1->elements[i * matrix1->cols + j] +
          matrix2->elements[i * matrix1->cols + j];

  return matrix;
}

Matrix *matrix_sub(Matrix *matrix1, Matrix *matrix2) {
  if (matrix1 == nullptr || matrix1->elements == nullptr ||
      matrix2 == nullptr || matrix2->elements == nullptr)
    return nullptr;
  if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols)
    return nullptr;

  Matrix *matrix = matrix_create(matrix1->rows, matrix1->cols);
  int i, j;

  #if HAVE_OPENMP
  #pragma omp parallel for private(i, j) shared(matrix1, matrix2, matrix)
  #endif
  for (i = 0; i < matrix1->rows; i++)
    for (j = 0; j < matrix1->cols; j++)
      matrix->elements[i * matrix1->cols + j] =
          matrix1->elements[i * matrix1->cols + j] -
          matrix2->elements[i * matrix1->cols + j];

  return matrix;
}

Matrix *matrix_dot(Matrix *matrix1, Matrix *matrix2) {
  if (matrix1 == nullptr || matrix1->elements == nullptr ||
      matrix2 == nullptr || matrix2->elements == nullptr)
    return nullptr;

  if (matrix1->cols != matrix2->rows) return nullptr;

  Matrix *matrix = matrix_create(matrix1->rows, matrix2->cols);
  int i, j, k;
  
  #if HAVE_OPENMP
  #pragma omp parallel for private(i, j, k) shared(matrix1, matrix2, matrix)
  #endif
  for (i = 0; i < matrix1->rows; i++)
    for (j = 0; j < matrix2->cols; j++)
      for (k = 0; k < matrix1->cols; k++)
        matrix->elements[i * matrix2->cols + j] +=
            matrix1->elements[i * matrix1->cols + k] *
            matrix2->elements[k * matrix2->cols + j];
            
  return matrix;
}

Matrix *matrix_mul_scalar(Matrix *matrix, double scalar) {
  if (matrix == nullptr || matrix->elements == nullptr) return nullptr;

  Matrix *new_matrix = matrix_create(matrix->rows, matrix->cols);
  int i, j;

  #ifdef USE_OPENMP
  #pragma omp parallel for private(i, j) shared(matrix, new_matrix)
  #endif
  for (i = 0; i < matrix->rows; i++)
    for (j = 0; j < matrix->cols; j++)
      new_matrix->elements[i * matrix->cols + j] =
          matrix->elements[i * matrix->cols + j] * scalar;

  return new_matrix;
}

Matrix *matrix_transpose(Matrix *matrix) {
  if (matrix == nullptr || matrix->elements == nullptr) return nullptr;

  Matrix *new_matrix = matrix_create(matrix->cols, matrix->rows);

  int i, j;

  #ifdef USE_OPENMP
  #pragma omp parallel for private(i, j) shared(matrix, new_matrix)
  #endif
  for (i = 0; i < matrix->rows; i++)
    for (j = 0; j < matrix->cols; j++)
      new_matrix->elements[j * matrix->rows + i] =
          matrix->elements[i * matrix->cols + j];

  return new_matrix;
}

Matrix *matrix_minor(Matrix *matrix, int row, int col) {
  Matrix *new_matrix = matrix_create(matrix->rows - 1, matrix->cols - 1);

  int new_row = 0, new_col = 0;
  int i, j;

  #ifdef USE_OPENMP
  #pragma omp parallel for private(i, j) shared(matrix, new_matrix)
  #endif
  for (i = 0; i < matrix->rows; i++) {
    if (i == row) continue;
    for (j = 0; j < matrix->cols; j++) {
      if (j == col) continue;
      new_matrix->elements[new_row * new_matrix->cols + new_col] =
          matrix->elements[i * matrix->cols + j];
      new_col++;
    }
    new_row++;
    new_col = 0;
  }

  return new_matrix;
}

double matrix_determinant(Matrix *matrix) {
  if (matrix->rows == 1) return matrix->elements[0];

  double determinant = 0;
  int i;
  Matrix *minor;

  #ifdef USE_OPENMP
  #pragma omp parallel for private(i, minor) shared(matrix, determinant)
  #endif
  for (i = 0; i < matrix->rows; i++) {
    minor = matrix_minor(matrix, 0, i);
    determinant +=
        matrix->elements[i] * matrix_determinant(minor) * (i % 2 == 0 ? 1 : -1);
    matrix_delete(minor);
  }

  return determinant;
}

Matrix *matrix_apply(Matrix *matrix, double (*function)(double)) {
  if (matrix == nullptr || matrix->elements == nullptr) return nullptr;

  Matrix *new_matrix = matrix_create(matrix->rows, matrix->cols);

  int i, j;
  
  #ifdef USE_OPENMP
  #pragma omp parallel for private(i, j) shared(matrix, new_matrix)
  #endif
  for (i = 0; i < matrix->rows; i++)
    for (j = 0; j < matrix->cols; j++)
      new_matrix->elements[i * matrix->cols + j] =
          function(matrix->elements[i * matrix->cols + j]);

  return new_matrix;
}

}  // namespace custom_math