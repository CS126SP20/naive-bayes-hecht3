// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef BAYES_CLASSIFIER_H_
#define BAYES_CLASSIFIER_H_


#include <istream>
#include <bayes/image.h>
#include <bayes/model.h>

namespace bayes {

  /**
   * Represents a Naive Bayes classifier that utilizes a provided model
   * containing probabilities to make the classifications
   */
  class Classifier {
  public:

  /**
    * The constructor for the classifier class. Takes in a model and a file
    * containing the images to be classified.
    *
    * @param model_file the file containing the model to be loaded
    * @param file_to_classify the file containing the images to be classified
    */
    Classifier(std::istream &model_file, std::istream &file_to_classify);

  /**
    * The method that does the classification. Does the calculation for the
    * probability that a pixel will be shaded for every pixel and then picks the
    * number that is most probable for the image to represent.
    *
    * @return the vector containing the classifications in order
    */
    std::vector<int> Classify();

    /**
    * Used to calculate the accuracy of a classifier. Is only called when
    * a labels file is given so that the results of the classification can
    * be checked against the labels.
    *
    * @return a percentage rounded to the nearest half percent representing
    *         the accuracy of the classifications
    */
    double CalculateAccuracy(const std::vector<int> &classifications,
      std::istream &labels_file);

    /**
    * Writes the classifications to a file so that they can be looked at by the
    * user
    *
    * @param classifications_file the file to write the classifications to
    * @param classifications the vector containing the classifications results
    */
    void SaveClassifications(std::ostream &classifications_file,
      const std::vector<int> &classifications);

    /**
    * Basic getter for the image list used in testing
    *
    * @return the list of images made by the constructor
    */
    std::vector<Image> GetImageList();

  private:

    /**
    * Splits a line containing a string of numbers separated by a space and
    * returns an array containing those numbers as doubles.
    *
    * @param line the line to be split by spaces
    * @return a vector of doubles representing the numbers in the given line
    */
    std::vector<double> split(const std::string &line);

    /** The array containing the logs of the probabilities.
     * Filled in the constructor.
     */
    double probs_logs_[kImageSize][kImageSize][kNumClasses][kNumShades];
    /** The list of Images representing each image in the provided file */
    std::vector<bayes::Image> image_list_;
    /** The list of priors used for calculating the probability of each image */
    std::vector<double> priors_;
  };
}  // namespace bayes

#endif  // BAYES_CLASSIFIER_H_

