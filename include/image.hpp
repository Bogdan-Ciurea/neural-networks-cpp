/**
 * @file image.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief This file is the header file for the image library that contains the
 *        image related functions that are used in the project.
 * @version 1.0
 * @date 2023-07-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <string.h>

#include <fstream>

#include "math.hpp"

namespace images {

#define MAX_LINE_LENGTH 1000000

typedef struct {
  int label;
  custom_math::Matrix *pixels;
} Image;

/**
 * @brief This function reads the images from the file and returns them as an
 *        array of Image structures.

 * It is the responsibility of the caller to free the memory allocated for the
 * images.
 *
 * @param  filename The name of the file from which the images are read.
 * @param  count    The number of images that are read.
 * @return Image*  The array of images that are read.
 */
Image **read_images(const char *filename, const int *count = nullptr);

/**
 * @brief This function reads the test images from the file and returns them as
 *        an array of Image structures.
 *
 * @return Image**  The array of images that are read.
 */
Image **read_test_images();

/**
 * @brief This function reads the training images from the file and returns
 * them as an array of Image structures.
 *
 * @return Image**  The array of images that are read.
 */
Image **read_train_images();

/**
 * @brief This function deletes the images that are passed as a parameter.
 *
 * @param images The images that are to be deleted.
 * @param count  The number of images that are to be deleted.
 */
void delete_images(Image **images, const size_t count = 0);

/**
 * @brief This function deletes the image that is passed as a parameter.
 *
 * @param image The image that is to be deleted.
 */
void delete_image(Image *image);

/**
 * @brief This function prints the image that is passed as a parameter.
 *
 * @param image The image that is to be printed.
 */
void print_image(const Image *image);

}  // namespace images

#endif  // IMAGE_HPP_