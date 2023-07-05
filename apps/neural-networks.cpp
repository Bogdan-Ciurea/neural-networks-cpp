/**
 * @file neural-networks.cpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief This file is the main file for the neural networks project.
 * @version 0.1
 * @date 2023-07-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "math.hpp"

int main() {
  custom_math::Matrix *matrix = custom_math::matrix_create(2, 2);
  custom_math::matrix_print(matrix);
  custom_math::matrix_delete(matrix);

#pragma omp parallel
  {
    // Get the thread number, and the maximum number of threads which depends on
    // the target architecture.
    int threadNum = omp_get_thread_num();
    int maxThreads = omp_get_max_threads();

    // Simple message to stdout
    printf("Hello from thread %i of %i!\n", threadNum, maxThreads);
  }
  return 0;
}