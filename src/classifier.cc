// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/classifier.h>
#include <nlohmann/json.hpp>
#include <sstream>
#include <iostream>

const int kiIndex = 0;
const int kjIndex = 1;
const int kClassIndex = 2;
const int kShadeIndex = 3;
const int kProbIndex = 4;
const int kPercentageMultiplier = 100;

bayes::Classifier::Classifier(std::istream &model_file,
                              std::istream &file_to_classify) {

  std::string model_line;
  int line_counter = 0;
// The logs of the probabilities in the model file are stored in the same way
// as the probabilities were stored in Model.cc
  while (std::getline(model_file, model_line)) {
    std::vector<double> model_vec = split(model_line);
    if (line_counter < kNumClasses) {
      priors_.push_back(model_vec[0]);
    } else {
      probs_logs_
      [(int) model_vec[kiIndex]]
      [(int) model_vec[kjIndex]]
      [(int) model_vec[kClassIndex]]
      [(int) model_vec[kShadeIndex]] = log(model_vec[kProbIndex]);
    }
    line_counter++;
  }

// Make the given classification txt into a string of characters and break them
// up into Images of [kImageSize][kImageSize]
  std::string classify_string;
  std::string classify_line;
  while (std::getline(file_to_classify, classify_line)) {
    std::istringstream iss(classify_line);
    classify_string.append(iss.str());
  }
  if (classify_string.length() > kImageSize * kImageSize) {
    for (int i = 0;
         i < classify_string.length(); i += kImageSize * kImageSize) {
      Image image(classify_string.substr(i, kImageSize * kImageSize));
      image_list_.push_back(image);
    }
  }
}

// Follwing function taken from
// https://codereview.stackexchange.com/questions/25212/input-reading-two-values-separated-by-whitespace-per-line
std::vector<double> bayes::Classifier::split(const std::string &line) {
  std::istringstream is(line);
  return std::vector<double>(std::istream_iterator<double>(is),
                             std::istream_iterator<double>());
}

std::vector<int> bayes::Classifier::Classify() {
  std::vector<int> classifications;
  double posterior_probability[kNumClasses];
  for (Image image : image_list_) {
// Zero initialize array for every image just to be safe.
    std::fill_n(posterior_probability, kNumClasses, 0.0);
    for (int c = 0; c < kNumClasses; c++) {
      for (int i = 0; i < kImageSize; i++) {
        for (int j = 0; j < kImageSize; j++) {
// Since we have the logs of the probabilities now, we can just add instead of
// multiplying to prevent integer underflow.
          posterior_probability[c]
            += probs_logs_[i][j][c][image.pixels_[i][j]];
        }
      }
    }
    double max = posterior_probability[0];
    int index_of_max = 0;
// Find the greatest posterior probability
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

double bayes::Classifier::CalculateAccuracy(
  const std::vector<int> &classifications, std::istream &labels_file) {

// Make a string containing the labels with no spaces or newlines
  std::string labels_string;
  std::string label_line;
  while (std::getline(labels_file, label_line)) {
    std::istringstream iss(label_line);
    labels_string.append(iss.str());
  }

// Find the number of correct classifications and divide that by the total
// total number of classifications
  int num_correct = 0;
  for (int i = 0; i < labels_string.length(); i++) {
    if (classifications[i] == ((int) labels_string[i] - '0')) {
      num_correct++;
    }
  }
  double percentage_correct =
    round(((double) num_correct
           / (double) labels_string.length()) * kPercentageMultiplier);
  return percentage_correct;
}

void
bayes::Classifier::SaveClassifications(std::ostream &classifications_file,
                                       const std::vector<int> &classifications) {

  std::string classifications_string;
  for (int classification : classifications) {
    classifications_string.append(std::to_string(classification));
    classifications_string.push_back('\n');
  }

  classifications_file << classifications_string;
}

std::vector<bayes::Image> bayes::Classifier::GetImageList() {
  return image_list_;
}



