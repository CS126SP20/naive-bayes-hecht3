// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/image.h>
#include <bayes/model.h>
#include <gflags/gflags.h>

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

DEFINE_string(name, "Clarice", "Your first name");
DEFINE_bool(happy, false, "Whether the greeting is a happy greeting");
DEFINE_string(training_images_file, "/home/connell/CLionProjects/naive-bayes-hecht3/data/digitdata/trainingimages",
  "The file containing the images to be used for training the classifier");
DEFINE_string(training_labels_file, "/home/connell/CLionProjects/naive-bayes-hecht3/data/digitdata/traininglabels",
  "The file containing the labels to be used for training the classifier");
DEFINE_string(training_target_file, "/home/connell/CLionProjects/naive-bayes-hecht3/data/TrainedModel.txt",
              "The location to save the trained model");


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

  std::ifstream model_in_stream(FLAGS_training_images_file);
  std::ifstream label_stream(FLAGS_training_labels_file);
  std::ofstream model_out_stream(FLAGS_training_target_file);

  if (model_in_stream.fail() || label_stream.fail() || model_out_stream.fail()) {
    std::cout << "\nInvalid file" << std::endl;
  } else {
    std::istream& model_input = model_in_stream;
    std::istream& label_input = label_stream;
    bayes::Model model(label_input, model_input);

    std::ostream& model_output = model_out_stream;
    model_output << model;
  }

  std::ifstream classify_model_in_stream(FLAGS_training_target_file);
  std::ifstream classify_labels_in_stream("/home/connell/CLionProjects/naive-bayes-hecht3/data/digitdata/testlabels");
  std::ifstream classify_images_in_stream("/home/connell/CLionProjects/naive-bayes-hecht3/data/digitdata/testimages");
  std::istream& classify_model_input = classify_model_in_stream;
  std::istream& classify_images_input = classify_images_in_stream;
  std::istream& classify_labels_input = classify_labels_in_stream;


  bayes::Classifier classifier(classify_model_input, classify_images_input);
  std::vector<int> classifications = classifier.classify();
  double accuracy_percentage = classifier.CalculateAccuracy(classifications, classify_labels_in_stream);
  std::cout << accuracy_percentage;
  return EXIT_SUCCESS;
}
