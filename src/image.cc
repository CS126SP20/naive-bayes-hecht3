// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/image.h>
#include <cmath>


namespace bayes {

  // Receives an image of length kImageSize and breaks it down into an array
  // representing whether or not a pixel is filled in that particular spot of
  // the image.
  std::istream &operator>>(std::istream &input, Image &image) {
    // The following iterator was taken from
    // https://en.cppreference.com/w/cpp/iterator/istreambuf_iterator
    std::string contents((std::istreambuf_iterator<char>(input)),
                         std::istreambuf_iterator<char>());
    image.as_string_.append(contents.c_str());
    for (int i = 0; i < kImageSize * kImageSize; i++) {
      if (image.as_string_[i] == ' ') {
        image.pixels_[(int) floor(i / kImageSize)][(int) i % kImageSize] = 0;
      } else if (image.as_string_[i] == '+' || image.as_string_[i] == '#') {
        image.pixels_[(int) floor(i / kImageSize)][(int) i % kImageSize] = 1;
      }
    }
    return input;
  }

  std::ostream &operator<<(std::ostream &output, Image const &image) {
    return output;
  }
}  // namespace bayes

