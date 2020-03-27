// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/model.h>
#include <nlohmann/json.hpp>
#include <sstream>
#include <fstream>
#include <map>

std::vector<bayes::Image> image_list_;

namespace bayes {
  const int kUnshadedIndex = 0;
  const int kShadedIndex = 1;

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

  std::vector<int> Model::ParseTrainingLabels(std::string labels_string) {
    std::vector<int> labels;
    for (int i = 0; i < labels_string.length(); i++) {
      labels.push_back(labels_string[i]);
    }
    return labels;
  }

  double Model::CalculateProbability(std::fstream labels_file) {
    // The following iterator was taken from
    // https://en.cppreference.com/w/cpp/iterator/istreambuf_iterator
    std::string contents((std::istreambuf_iterator<char>(labels_file)),
                         std::istreambuf_iterator<char>());
    std::string labels_string;
    labels_string.append(contents);
    // Labels will have the same index as the contents of image list
    std::vector<int> labels = ParseTrainingLabels(labels_string);

    std::map<int, int> class_occurrences;
    for (int i = 0; i < kNumClasses; i++) {
      class_occurrences.insert(std::make_pair(i, 0));
    }
    for (int i = 0; i < labels.size(); i++) {
      class_occurrences.find(i) -> second++;
    }

    int shade_occurrences[kImageSize][kImageSize][kNumClasses][kNumShades];
    for (int image = 0; image < image_list_.size(); image++) {
      for (int i = 0; i < kImageSize; i++) {
        for (int j = 0; j < kImageSize; j++) {
          if (image_list_[image].pixels_[i][j] == 0) {
            shade_occurrences[i][j][labels[image]][kUnshadedIndex]++;
          } else if (image_list_[image].pixels_[i][j] == 1) {
            shade_occurrences[i][j][labels[image]][kShadedIndex]++;
          }
        }
      }
    }

    for (int i = 0; i < kImageSize; i++) {
      for (int j = 0; j < kImageSize; j++) {
        for (int c = 0; c < kNumClasses; c++) {
          for (int s = 0; s < kNumShades; s++) {
            double probability =
              (kLaplaceConstant + shade_occurrences[i][j][c][s])
            / (kLaplaceDenomMultiplier * kLaplaceConstant
                + class_occurrences.at(c));
            probs_[i][j][c][s] = probability;
          }
        }
      }
    }
  }


}  // namespace bayes
