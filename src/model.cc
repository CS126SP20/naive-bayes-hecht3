// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/model.h>
#include <nlohmann/json.hpp>
#include <sstream>

std::vector<bayes::Image> image_list_;

namespace bayes {
  std::istream &operator>>(std::istream &input, Model const &model) {
    // The following iterator was taken from
    // https://en.cppreference.com/w/cpp/iterator/istreambuf_iterator
    std::string contents((std::istreambuf_iterator<char>(input)),
                         std::istreambuf_iterator<char>());
    std::string model_string;
    model_string.append(contents);
    if (model_string.length() > kImageSize) {
      for (int i = 0; i < model_string.length(); i+= kImageSize) {
        Image image(model_string.substr(i, kImageSize));
        image_list_.push_back(image);
      }
    }
    return input;
  }

}  // namespace bayes
