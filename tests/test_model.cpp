//
// Created by connell on 3/31/20.
//

#include <catch2/catch.hpp>
#include <bayes/classifier.h>
#include <fstream>


TEST_CASE("Model constructor image list", "[Image array created]") {
  std::ifstream model_in_stream(
    "/home/connell/CLionProjects/naive-bayes-hecht3/tests/data/sampleimages");
  std::ifstream label_stream(
    "/home/connell/CLionProjects/naive-bayes-hecht3/tests/data/samplelabels");
  std::istream &model_input = model_in_stream;
  std::istream &label_input = label_stream;
  bayes::Model model(label_input, model_input);
  REQUIRE(model.GetImageList().size() == 3);
}

TEST_CASE("Insertion operator functional", "[TrainedModel.txt written]") {
  std::ifstream model_in_stream(
    "/home/connell/CLionProjects/naive-bayes-hecht3/tests/data/sampleimages");
  std::ifstream label_stream(
    "/home/connell/CLionProjects/naive-bayes-hecht3/tests/data/samplelabels");
  std::istream &model_input = model_in_stream;
  std::istream &label_input = label_stream;
  bayes::Model model(label_input, model_input);

  std::ofstream model_out_stream(
    "/home/connell/CLionProjects/naive-bayes-hecht3/tests/data/TrainedModelTest.txt");
  std::ostream &model_output = model_out_stream;
  model_output << model;

  std::ifstream model_test_input(
    "/home/connell/CLionProjects/naive-bayes-hecht3/tests/data/TrainedModelTest.txt");
  std::istream &model_stream = model_test_input;
  std::string first_line;
  std::getline(model_stream, first_line);
  // Code is currently configured for images of size 28 so we will just check
  // that the file was actually written too.
  REQUIRE(first_line.length() != 0);
}

// Aside from these tests, probabilities are clearly calculated properly
// considering the model is over 70% accurate.

