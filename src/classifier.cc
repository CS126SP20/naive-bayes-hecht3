// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/classifier.h>
#include <nlohmann/json.hpp>
#include <sstream>
#include <iostream>

std::vector<double> split(const std::string& line);

std::vector<bayes::Image> image_list;

const int kiIndex = 0;
const int kjIndex = 1;
const int kClassIndex = 2;
const int kShadeIndex = 3;
const int kProbIndex = 4;

namespace bayes {
  
}  // namespace bayes

bayes::Classifier::Classifier(std::istream &model_file, std::istream &file_to_classify) {
  std::string model_line;
  while (std::getline(model_file, model_line)) {
    std::vector<double> model_vec = split(model_line);
    probs_logs_[(int) model_vec[kiIndex]][(int) model_vec[kjIndex]][(int) model_vec[kClassIndex]]
      [(int) model_vec[kShadeIndex]] = log(model_vec[kProbIndex]);
  }

  std::string classify_string;
  std::string classify_line;
  while (std::getline(file_to_classify, classify_line)) {
    std::istringstream iss(classify_line);
    classify_string.append(iss.str());
  }
  if (classify_string.length() > kImageSize * kImageSize) {
    for (int i = 0; i < classify_string.length(); i += kImageSize * kImageSize) {
      Image image(classify_string.substr(i, kImageSize * kImageSize));
      image_list.push_back(image);
    }
  }
}

// Follwing function taken from
// https://codereview.stackexchange.com/questions/25212/input-reading-two-values-separated-by-whitespace-per-line
std::vector<double> split(const std::string& line) {
  std::istringstream is(line);
  return std::vector<double>(std::istream_iterator<double>(is), std::istream_iterator<double>());
}