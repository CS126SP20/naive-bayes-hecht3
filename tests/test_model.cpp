//
// Created by connell on 3/31/20.
//

#include <catch2/catch.hpp>
#include <bayes/classifier.h>
#include <fstream>


TEST_CASE("Constructor image list", "[Image array created]") {
  std::ifstream model_in_stream(
    "/home/connell/CLionProjects/naive-bayes-hecht3/tests/data/sampleimages");
  std::ifstream label_stream(
    "/home/connell/CLionProjects/naive-bayes-hecht3/tests/data/samplelabels");
  std::istream &model_input = model_in_stream;
  std::istream &label_input = label_stream;
  bayes::Model model(label_input, model_input);
  REQUIRE(model.GetImageList().size() == 3);
}