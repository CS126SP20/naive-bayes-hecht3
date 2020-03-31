// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef BAYES_IMAGE_H_
#define BAYES_IMAGE_H_

#include <cstdlib>
#include <istream>


namespace bayes {

constexpr size_t kImageSize = 28;

class Image {
public:
/**
  * The constructor for the Image class. Initializes an image containing an
  * array of pixel representing whether or not a pixel is shaded
  *
  * @param img_string a string containing the pixels for the image of size
  *        kImageSize * kImageSize
  */
  Image(const std::string &img_string);

/**
  * An array representing pixels. Values are 0 if the pixel is unshaded, 1
  * if the pixel is shaded for the corresponding location [][].
  */
  int pixels_[kImageSize][kImageSize];
};

}  // namespace bayes

#endif  // BAYES_IMAGE_H_
