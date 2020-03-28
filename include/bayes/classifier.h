// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef BAYES_CLASSIFIER_H_
#define BAYES_CLASSIFIER_H_


#include <istream>
#include <bayes/image.h>
#include <bayes/model.h>

namespace bayes {
  class Classifier {
  public:
    Classifier(std::istream &model_file, std::istream &file_to_classify);
  private:
    double probs_logs_[kImageSize][kImageSize][kNumClasses][kNumShades];
    std::vector<bayes::Image> image_list_;
    std::vector<double> priors_;

    std::vector<int> classify();
  };
}  // namespace bayes

#endif  // BAYES_CLASSIFIER_H_

