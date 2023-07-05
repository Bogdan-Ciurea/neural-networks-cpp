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

Matrix *matrix_create(int rows, int cols) {
  if (rows <= 0 || cols <= 0) return nullptr;

  Matrix *matrix = new Matrix;
  matrix->rows = rows;
  matrix->cols = cols;
  matrix->elements = new double[rows * cols];
  return matrix;
}

Matrix *matrix_I(int size) {
  Matrix *matrix = matrix_create(size, size);

#ifdef OPENMP_AVAILABLE
#pragma omp parallel for
#endif
  for (int i = 0; i < size; i++) {
    matrix->elements[i * size + i] = 1;
  }

#ifdef OPENMP_AVAILABLE
  std::print("OpenMP is available\n");
#endif

  return matrix;
}

void matrix_delete(Matrix *matrix) {
  if (matrix == nullptr) return;

  delete[] matrix->elements;
  matrix->elements = nullptr;
  delete matrix;
  matrix = nullptr;
}

void matrix_print(Matrix *matrix) {
  if (matrix == nullptr || matrix->elements == nullptr) return;

  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->cols; j++) {
      printf("%f ", matrix->elements[i * matrix->cols + j]);
    }
    printf("\n");
  }
}

Matrix *matrix_copy(Matrix *matrix) {
  if (matrix == nullptr || matrix->elements == nullptr) return nullptr;

  Matrix *new_matrix = matrix_create(matrix->rows, matrix->cols);

  for (int i = 0; i < matrix->rows; i++)
    for (int j = 0; j < matrix->cols; j++)
      new_matrix->elements[i * matrix->cols + j] =
          matrix->elements[i * matrix->cols + j];

  return new_matrix;
}

void matrix_save(Matrix *matrix, const char *filename) {
  FILE *file = fopen(filename, "w");

  fprintf(file, "%d %d\n", matrix->rows, matrix->cols);

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

  int rows, cols;
  fscanf(file, "%d %d", &rows, &cols);

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

  for (int i = 0; i < matrix1->rows; i++)
    for (int j = 0; j < matrix1->cols; j++)
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

  for (int i = 0; i < matrix1->rows; i++)
    for (int j = 0; j < matrix1->cols; j++)
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

  for (int i = 0; i < matrix1->rows; i++)
    for (int j = 0; j < matrix2->cols; j++)
      for (int k = 0; k < matrix1->cols; k++)
        matrix->elements[i * matrix2->cols + j] +=
            matrix1->elements[i * matrix1->cols + k] *
            matrix2->elements[k * matrix2->cols + j];

  return matrix;
}

Matrix *matrix_mul_scalar(Matrix *matrix, double scalar) {
  if (matrix == nullptr || matrix->elements == nullptr) return nullptr;

  Matrix *new_matrix = matrix_create(matrix->rows, matrix->cols);

  for (int i = 0; i < matrix->rows; i++)
    for (int j = 0; j < matrix->cols; j++)
      new_matrix->elements[i * matrix->cols + j] =
          matrix->elements[i * matrix->cols + j] * scalar;

  return new_matrix;
}

Matrix *matrix_transpose(Matrix *matrix) {
  if (matrix == nullptr || matrix->elements == nullptr) return nullptr;

  Matrix *new_matrix = matrix_create(matrix->cols, matrix->rows);

  for (int i = 0; i < matrix->rows; i++)
    for (int j = 0; j < matrix->cols; j++)
      new_matrix->elements[j * matrix->rows + i] =
          matrix->elements[i * matrix->cols + j];

  return new_matrix;
}

Matrix *matrix_minor(Matrix *matrix, int row, int col) {
  Matrix *new_matrix = matrix_create(matrix->rows - 1, matrix->cols - 1);

  int new_row = 0, new_col = 0;

  for (int i = 0; i < matrix->rows; i++) {
    if (i == row) continue;
    for (int j = 0; j < matrix->cols; j++) {
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

  for (int i = 0; i < matrix->rows; i++) {
    Matrix *minor = matrix_minor(matrix, 0, i);
    determinant +=
        matrix->elements[i] * matrix_determinant(minor) * (i % 2 == 0 ? 1 : -1);
    matrix_delete(minor);
  }

  return determinant;
}

Matrix *matrix_apply(Matrix *matrix, double (*function)(double)) {
  if (matrix == nullptr || matrix->elements == nullptr) return nullptr;

  Matrix *new_matrix = matrix_create(matrix->rows, matrix->cols);

  for (int i = 0; i < matrix->rows; i++)
    for (int j = 0; j < matrix->cols; j++)
      new_matrix->elements[i * matrix->cols + j] =
          function(matrix->elements[i * matrix->cols + j]);

  return new_matrix;
}

}  // namespace custom_math