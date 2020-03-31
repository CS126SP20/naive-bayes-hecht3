// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/image.h>
#include <cmath>
#include <bayes/model.h>
#include <iostream>


namespace bayes {

}  // namespace bayes

// Receives an image of length kImageSize and breaks it down into an array
// representing whether or not a pixel is filled in that particular spot of
// the image.
bayes::Image::Image(std::string img_string) {
  image_as_string_ = img_string;
  if (img_string.find_first_not_of("#+ ") != std::string::npos) {
    std::cout << "One or more images contained invalid characters";
    exit(1);
  }
  for (int i = 0; i < kImageSize * kImageSize; i++) {
    if (image_as_string_[i] == ' ') {
      pixels_[(int) floor(i / kImageSize)][(int) i % kImageSize] = 0;
    } else if (image_as_string_[i] == '+' || image_as_string_[i] == '#') {
      pixels_[(int) floor(i / kImageSize)][(int) i % kImageSize] = 1;
    }
  }
}
