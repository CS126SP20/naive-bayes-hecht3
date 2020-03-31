// Copyright (c) 2020 [Your Name]. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <bayes/classifier.h>


TEST_CASE("Classifier constructor image list", "[Image array created]") {
  std::ifstream classifier_in_stream(
    "/home/connell/CLionProjects/naive-bayes-hecht3/tests/data/sampleimages");
  std::ifstream classifier_label_stream(
    "/home/connell/CLionProjects/naive-bayes-hecht3/tests/data/samplelabels");
  std::istream &classify_input = classifier_in_stream;
  std::istream &label_input = classifier_label_stream;
  bayes::Classifier classifier(label_input, classify_input);
  REQUIRE(classifier.GetImageList().size() == 3);
}

TEST_CASE("Classifier accuracy", "[accuracy > 70%]") {
  std::ifstream classifier_in_stream(
    "/home/connell/CLionProjects/naive-bayes-hecht3/data/digitdata/testimages");
  std::ifstream classifier_model_stream(
    "/home/connell/CLionProjects/naive-bayes-hecht3/data/TrainedModel.txt");
  std::istream &classify_input = classifier_in_stream;
  std::istream &model_input = classifier_model_stream;
  bayes::Classifier classifier(model_input, classify_input);
  std::vector<int> classifications = classifier.classify();
  std::ifstream classify_labels_in_stream(
    "/home/connell/CLionProjects/naive-bayes-hecht3/data/digitdata/testlabels");
  std::istream &classify_labels_input = classify_labels_in_stream;

  double accuracy = classifier.CalculateAccuracy(
    classifications, classify_labels_in_stream);
  REQUIRE(accuracy > 70);
}

TEST_CASE("Classifier save", "[classifications saved]") {
  std::ifstream classifier_in_stream(
    "/home/connell/CLionProjects/naive-bayes-hecht3/data/digitdata/testimages");
  std::ifstream classifier_model_stream(
    "/home/connell/CLionProjects/naive-bayes-hecht3/data/TrainedModel.txt");
  std::istream &classify_input = classifier_in_stream;
  std::istream &model_input = classifier_model_stream;
  bayes::Classifier classifier(model_input, classify_input);
  std::vector<int> classifications = classifier.classify();
  std::ofstream classifications_target_ofstream(
    "/home/connell/CLionProjects/naive-bayes-hecht3/tests/data/ClassificationsTest.txt");
  std::ostream &classifications_target = classifications_target_ofstream;
  classifier.SaveClassifications(classifications_target, classifications);

  std::ifstream classifier_test_input(
    "/home/connell/CLionProjects/naive-bayes-hecht3/tests/data/ClassificationsTest.txt");
  std::istream &classifier_stream = classifier_test_input;
  std::string first_line;
  std::getline(classifier_stream, first_line);
  std::cout << first_line;
  REQUIRE(first_line.length() != 0);
}

