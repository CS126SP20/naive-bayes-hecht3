// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/image.h>
#include <bayes/model.h>
#include <gflags/gflags.h>

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

DEFINE_string(training_images_file,
              "/home/connell/CLionProjects/naive-bayes-hecht3/data/digitdata/trainingimages",
              "The file containing the images to be used for training the classifier");
DEFINE_string(training_labels_file,
              "/home/connell/CLionProjects/naive-bayes-hecht3/data/digitdata/traininglabels",
              "The file containing the labels to be used for training the classifier");
DEFINE_string(training_target_file,
              "/home/connell/CLionProjects/naive-bayes-hecht3/data/TrainedModel.txt",
              "The location to save the trained model");
DEFINE_string(classify_images_file,
              "/home/connell/CLionProjects/naive-bayes-hecht3/data/digitdata/testimages",
              "The file containing text representing images to be classified");
DEFINE_string(classify_labels_file,
              "/home/connell/CLionProjects/naive-bayes-hecht3/data/digitdata/testlabels",
              "The file containing labels for the images to be classified. "
              "Only used when testing accuracy");
DEFINE_string(classify_target_file,
              "/home/connell/CLionProjects/naive-bayes-hecht3/data/Classifications.txt",
              "The file containing labels for the images to be classified. "
              "Only used when testing accuracy");

int main(int argc, char **argv) {
  gflags::SetUsageMessage(
    "Trains an image classifier and/or classifies given images. "
    "Pass --helpshort for options.");

  gflags::ParseCommandLineFlags(&argc, &argv, true);

  bool none_or_all_training_commands_provided =
    ((gflags::GetCommandLineFlagInfoOrDie("training_images_file").is_default
      && gflags::GetCommandLineFlagInfoOrDie("training_labels_file").is_default
      && gflags::GetCommandLineFlagInfoOrDie("training_target_file").is_default)
     || (!gflags::GetCommandLineFlagInfoOrDie("training_images_file").is_default
      && !gflags::GetCommandLineFlagInfoOrDie("training_labels_file").is_default
      && !gflags::GetCommandLineFlagInfoOrDie("training_target_file").is_default));

  // Excludes the classification labels file because that one isn't required
  bool none_or_all_required_classification_commands_provided =
    ((gflags::GetCommandLineFlagInfoOrDie("classify_images_file").is_default
      && gflags::GetCommandLineFlagInfoOrDie("classify_target_file").is_default)
     || (!gflags::GetCommandLineFlagInfoOrDie("classify_images_file").is_default
      && !gflags::GetCommandLineFlagInfoOrDie("classify_target_file").is_default));

  if (!none_or_all_training_commands_provided
      || !none_or_all_required_classification_commands_provided) {
    std::cerr << "If you would like to train a model, please provide "
                 "an images file, a labels file, and a target file "
                 "to store the model."
                 "\nIf you would like to classify images, please provide "
                 "an images file and a target file to store the "
                 "classifications" << std::endl;
    return EXIT_FAILURE;
  } else if (!FLAGS_training_images_file.empty()
             && !FLAGS_training_labels_file.empty()
             && !FLAGS_training_target_file.empty()) {
    std::ifstream model_in_stream(FLAGS_training_images_file);
    std::ifstream label_stream(FLAGS_training_labels_file);
    std::ofstream model_out_stream(FLAGS_training_target_file);

    if (model_in_stream.fail()
        || label_stream.fail()
        || model_out_stream.fail()) {
      std::cout << "\nOne or more provided model files was invalid"
        << std::endl;
      return EXIT_FAILURE;
    } else {
      std::istream &model_input = model_in_stream;
      std::istream &label_input = label_stream;
      bayes::Model model(label_input, model_input);

      std::ostream &model_output = model_out_stream;
      model_output << model;
      std::cout << "\nModel trained!" << std::endl;
    }
  }

  if (!FLAGS_classify_images_file.empty()
      && !FLAGS_classify_target_file.empty()) {

    std::ifstream model_in_stream(FLAGS_training_target_file);
    std::ifstream images_in_stream(FLAGS_classify_images_file);
    std::istream &classify_model_input = model_in_stream;
    std::istream &classify_images_input = images_in_stream;

    std::ofstream classify_out_stream(FLAGS_classify_target_file);
    std::ostream &classifications_output(classify_out_stream);

    if (classify_model_input.fail()
        || classify_images_input.fail()
        || classify_out_stream.fail()) {
      std::cout << "\nOne or more provided classification files was invalid"
        << std::endl;
      return EXIT_FAILURE;
    } else {
      std::istream &model_input = model_in_stream;
      bayes::Classifier classifier(classify_model_input, classify_images_input);
      std::vector<int> classifications = classifier.classify();
      classifier.SaveClassifications(classifications_output, classifications);

      if (!FLAGS_classify_labels_file.empty()) {
        std::ifstream classify_labels_in_stream(FLAGS_classify_labels_file);
        std::istream &classify_labels_input = classify_labels_in_stream;

        if (classify_labels_in_stream.fail()) {
          std::cout << "\nThe classification labels input file was invalid"
                    << std::endl;
          return EXIT_FAILURE;
        } else {
          double accuracy_percentage =
            classifier.CalculateAccuracy(classifications,
                                         classify_labels_in_stream);
          std::cout << accuracy_percentage;
        }
      }
    }

  }

  return EXIT_SUCCESS;

}

