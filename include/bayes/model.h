// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef BAYES_MODEL_H_
#define BAYES_MODEL_H_

#include "image.h"

#include <cstdlib>
#include <vector>


namespace bayes {

  /** 0-9 inclusive. */
  constexpr size_t kNumClasses = 10;
  /** Shaded or not shaded. */
  constexpr size_t kNumShades = 2;


  // Represents a Naive Bayes classification model for determining the
  // likelihood that an individual pixel for an individual class is
  // white or black.

 /**
   * Represents a Naive Bayes classification model for determining the
   * likelihood that an individual pixel for an individual class is
   * white or black.
   */
  class Model {
  public:

  /**
    * The constructor for the Model class. Initializes the array of images from
    * the training file and calls on CalculateProbabilities to create the
    * probabilities array
    *
    * @param labels_file the file containing the labels corresponding to the
    *        provided images
    * @param train_file the file containing the images to train the model on
    */
    Model(std::istream &labels_file, std::istream &train_file);


  /**
    * The overloaded insertion operator for a Model instance. Writes the model
    * to a provided file.
    *
    * @param output the output to write to
    * @param model the model instance
    */
    friend std::ostream &operator<<(std::ostream &output, const Model &model);

  /**
    * Called on by the constructor to calculate the probabilities for the model
    *
    * @param labels_string a string containing all the labels that correspond
    *        to the training images
    */
    void CalculateProbabilities(const std::string &labels_string);

  /**
    * Basic getter for the image list used for testing
    *
    * @return the list of images made by the constructor
    */
    std::vector<bayes::Image> GetImageList();

    // The individual probabilities for each pixel for each class for
    // whether it's shaded or not.
    //
    // Examples:
    // probs[2][10][7][0] is the computed probability that a pixel at
    // [2][10] for class 7 is not shaded.
    //
    // probs[0][0][0][1] is the computed probability that a pixel at
    // [0][0] for class 0 is shaded.
  private:

  /**
    * The individual probabilities for each pixel for each class for
    * whether it's shaded or not.
    * Examples:
    * probs[2][10][7][0] is the computed probability that a pixel at
    * [2][10] for class 7 is not shaded.
    * probs[0][0][0][1] is the computed probability that a pixel at
    * [0][0] for class 0 is shaded.
    */
    double probs_[kImageSize][kImageSize][kNumClasses][kNumShades];

    /**
    * The array containing priors for each class.
    * Array index corresponds to the class.
    */
    double priors_[kNumClasses];

    /** The list of Images representing each image in the provided file */
    std::vector<bayes::Image> image_list_;
  };

}  // namespace bayes

#endif  // BAYES_MODEL_H_
