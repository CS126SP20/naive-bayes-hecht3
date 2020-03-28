// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/classifier.h>
#include <nlohmann/json.hpp>
#include <sstream>
#include <iostream>

std::vector<double> split(const std::string& line);

const int kiIndex = 0;
const int kjIndex = 1;
const int kClassIndex = 2;
const int kShadeIndex = 3;
const int kProbIndex = 4;

namespace bayes {
  
}  // namespace bayes

bayes::Classifier::Classifier(std::istream &model_file, std::istream &file_to_classify) {
  std::string model_line;
  int line_counter = 0;
  while (std::getline(model_file, model_line)) {
    std::vector<double> model_vec = split(model_line);
    if (line_counter < kNumClasses) {
      priors_.push_back(model_vec[0]);
    } else {
      probs_logs_[(int) model_vec[kiIndex]][(int) model_vec[kjIndex]][(int) model_vec[kClassIndex]]
      [(int) model_vec[kShadeIndex]] = log(model_vec[kProbIndex]);
    }
    line_counter++;
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
      image_list_.push_back(image);
    }
  }
}

// Follwing function taken from
// https://codereview.stackexchange.com/questions/25212/input-reading-two-values-separated-by-whitespace-per-line
std::vector<double> split(const std::string& line) {
  std::istringstream is(line);
  return std::vector<double>(std::istream_iterator<double>(is), std::istream_iterator<double>());
}

// Returns a vector containing the classifications
std::vector<int> bayes::Classifier::classify() {
  std::vector<int> classifications;
  double posterior_probability[kNumClasses];
  for (int image = 0; image < image_list_.size(); image++) {
    std::fill_n(posterior_probability, kNumClasses, 0.0);
    for (int c = 0; c < kNumClasses; c++) {
      for (int i = 0; i < kImageSize; i++) {
        for (int j = 0; j < kImageSize; j++) {
          posterior_probability[c] += probs_logs_[i][j][c][image_list_[image].pixels_[i][j]];
        }
      }
    }
    double max = posterior_probability[0];
    int index_of_max = 0;
    for (int p = 0; p < kNumClasses; p++) {
      if (posterior_probability[p] > max) {
        max = posterior_probability[p];
        index_of_max = p;
      }
    }
    classifications.push_back(index_of_max);
  }
  return classifications;
}

double bayes::Classifier::CalculateAccuracy(const std::vector<int> classifications, std::istream &labels_file) {
  std::string labels_string;
  std::string label_line;
  while (std::getline(labels_file, label_line)) {
    std::istringstream iss(label_line);
    labels_string.append(iss.str());
  }

  int num_correct = 0;
  for (int i = 0; i < labels_string.length(); i++) {
    if (classifications[i] == ((int) labels_string[i] - '0')) {
      num_correct++;
    }
  }
  double percentage_correct = round(((double) num_correct / (double) labels_string.length()) * 100);
  return percentage_correct;
}