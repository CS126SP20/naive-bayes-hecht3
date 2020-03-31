// Copyright (c) 2020 [Your Name]. All rights reserved.


#include <catch2/catch.hpp>
#include <bayes/image.h>

// This is literally the only functionality of image (the constructor) so
// all we need to do is test a 28x28 input and make sure the pixels array is
// initial initialized properly.
TEST_CASE("Initialization", "[constructor]") {
  bayes::Image image(" # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     "                            "
                     "############################"
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     " # + ++++++++++++++         "
                     "++++++++++++++++++++++++++++");
  REQUIRE(image.pixels_[0][0] == 0);
  REQUIRE(image.pixels_[0][1] == 1);
  REQUIRE(image.pixels_[0][2] == 0);
  REQUIRE(image.pixels_[0][3] == 1);
  REQUIRE(image.pixels_[1][0] == 0);
  REQUIRE(image.pixels_[1][3] == 1);
  REQUIRE(image.pixels_[2][0] == 0);
  REQUIRE(image.pixels_[2][3] == 1);
  REQUIRE(image.pixels_[3][0] == 0);
  REQUIRE(image.pixels_[3][3] == 0);
  REQUIRE(image.pixels_[4][0] == 1);
  REQUIRE(image.pixels_[4][1] == 1);
  REQUIRE(image.pixels_[4][2] == 1);
  REQUIRE(image.pixels_[4][3] == 1);
  REQUIRE(image.pixels_[4][4] == 1);
  REQUIRE(image.pixels_[4][14] == 1);
  REQUIRE(image.pixels_[4][15] == 1);
  REQUIRE(image.pixels_[4][27] == 1);
  REQUIRE(image.pixels_[5][24] == 0);
  REQUIRE(image.pixels_[27][2] == 1);
  REQUIRE(image.pixels_[27][5] == 1);
  REQUIRE(image.pixels_[27][22] == 1);
  REQUIRE(image.pixels_[27][23] == 1);
  REQUIRE(image.pixels_[27][27] == 1);
}
