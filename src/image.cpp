/**
 * @file image.cpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief  This file contains the implementation of the functions declared in
 *         image.hpp.
 * @version 1.0
 * @date 2023-07-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "image.hpp"

namespace images {

Image **read_images(const char *filename, const int *count) {
  Image **images = nullptr;

  FILE *file = fopen(filename, "r");

  if (file == nullptr || count == nullptr) {
    return nullptr;
  }

  printf("Reading %d image(s) from %s...\n", *count, filename);

  images = (Image **)malloc((*count) * sizeof(Image *));

  if (images == nullptr) {
    fclose(file);
    return nullptr;
  }

  char line[MAX_LINE_LENGTH];
  int i = 0;

  fgets(line, MAX_LINE_LENGTH, file);

  while (feof(file) != 1 && i < *count) {
    // Allocate memory for the image
    images[i] = (Image *)malloc(sizeof(Image));

    if (images[i] == nullptr) {
      fclose(file);
      return nullptr;
    }

    // Allocate memory for the pixels
    images[i]->pixels = custom_math::matrix_create(28, 28);

    if (images[i]->pixels == nullptr) {
      // Delete the current image and all the previous ones
      while (i >= 0) {
        delete_image(images[i]);
        i--;
      }
      fclose(file);
      return nullptr;
    }

    // Process the line
    int j = 0;
    fgets(line, MAX_LINE_LENGTH, file);
    char *token = strtok(line, ",");
    images[i]->label = atoi(token);

    // Read the pixels
    while (token != nullptr) {
      token = strtok(nullptr, ",");
      if (token != nullptr) {
        images[i]->pixels->elements[j - 1] = atof(token) / 255.0;
        j++;
      }
    }

    // Go to the next line
    i++;
  }

  return images;
}

Image **read_test_images() {
  const char *filename = "data/mnist_test.csv";
  int count = 10000;

  return read_images(filename, &count);
}

Image **read_train_images() {
  const char *filename = "data/mnist_train.csv";
  int count = 60000;

  return read_images(filename, &count);
}

void delete_images(Image **images, const size_t count) {
  if (images == nullptr) {
    return;
  }

  int i = 0;
  while (i < count) {
    delete_image(images[i]);
    i++;
  }

  free(images);
}

void delete_image(Image *image) {
  if (image == nullptr) {
    return;
  }
  custom_math::matrix_delete(image->pixels);
  printf("Deleting image...\n");
  free(image);
}

void print_image(const Image *image) {
  if (image == nullptr) {
    printf("Image is null.\n");
    return;
  }

  printf("Image:\nRows: %ld Columns: %ld\n", image->pixels->rows,
         image->pixels->cols);
  printf("Image label: %d\n", image->label);
  custom_math::matrix_print(image->pixels);
}

}  // namespace images