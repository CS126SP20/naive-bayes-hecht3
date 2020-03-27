// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/image.h>
#include <bayes/model.h>
#include <gflags/gflags.h>

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>


// TODO(you): Change the code below for your project use case.

DEFINE_string(name, "Clarice", "Your first name");
DEFINE_bool(happy, false, "Whether the greeting is a happy greeting");
DEFINE_string(training_images_file, "/home/connell/CLionProjects/naive-bayes-hecht3/data/digitdata/trainingimages",
  "The file containing the images to be used for training the classifier");
DEFINE_string(training_labels_file, "/home/connell/CLionProjects/naive-bayes-hecht3/data/digitdata/traininglabels",
  "The file containing the labels to be used for training the classifier");


int main(int argc, char** argv) {
  gflags::SetUsageMessage(
      "Greets you with your name. Pass --helpshort for options.");

  gflags::ParseCommandLineFlags(&argc, &argv, true);

  if (FLAGS_name.empty()) {
    std::cerr << "Please provide a name via the --name flag." << std::endl;
    return EXIT_FAILURE;
  }

  // GetLine for the entire file in main to parse it to a string so that we can
  // call the overloaded extraction operator on every 28 lines. Ideally we don't
  // loop through the string twice...

  const std::string punctuation = FLAGS_happy ? "!" : ".";

  std::ifstream model_stream(FLAGS_training_images_file);
  if (model_stream.fail()) {
    std::cout << "\nInvalid file" << std::endl;
  } else {
    bayes::Model model;
    std::istream& input_stream = model_stream;
    input_stream >> model;
    std::ifstream label_stream(FLAGS_training_labels_file);
    std::istream& label_input = label_stream;
    model.CalculateProbabilities(label_input);
  }

  std::cout << "Hello, " << FLAGS_name << punctuation << std::endl;
  return EXIT_SUCCESS;
}
