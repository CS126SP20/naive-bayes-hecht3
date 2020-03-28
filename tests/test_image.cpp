// Copyright (c) 2020 [Your Name]. All rights reserved.


#include <catch2/catch.hpp>
#include <bayes/image.h>


// TODO(you): Remove this unnecessary test case.
TEST_CASE("test", "[addition]") {
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
  REQUIRE(image.pixels_[1][1] == 1);
  REQUIRE(image.pixels_[1][2] == 0);
  REQUIRE(image.pixels_[1][3] == 1);
  REQUIRE(image.pixels_[2][0] == 0);
  REQUIRE(image.pixels_[2][1] == 1);
  REQUIRE(image.pixels_[2][2] == 0);
  REQUIRE(image.pixels_[2][3] == 1);

  REQUIRE(image.pixels_[3][0] == 0);
  REQUIRE(image.pixels_[3][1] == 0);
  REQUIRE(image.pixels_[3][2] == 0);
  REQUIRE(image.pixels_[3][3] == 0);

  REQUIRE(image.pixels_[4][0] == 1);
  REQUIRE(image.pixels_[4][1] == 1);
  REQUIRE(image.pixels_[4][2] == 1);
  REQUIRE(image.pixels_[4][3] == 1);
  REQUIRE(image.pixels_[4][4] == 1);
  REQUIRE(image.pixels_[4][5] == 1);
  REQUIRE(image.pixels_[4][6] == 1);
  REQUIRE(image.pixels_[4][7] == 1);
  REQUIRE(image.pixels_[4][8] == 1);
  REQUIRE(image.pixels_[4][9] == 1);
  REQUIRE(image.pixels_[4][10] == 1);
  REQUIRE(image.pixels_[4][11] == 1);
  REQUIRE(image.pixels_[4][12] == 1);
  REQUIRE(image.pixels_[4][13] == 1);
  REQUIRE(image.pixels_[4][14] == 1);
  REQUIRE(image.pixels_[4][15] == 1);
  REQUIRE(image.pixels_[4][16] == 1);
  REQUIRE(image.pixels_[4][17] == 1);
  REQUIRE(image.pixels_[4][18] == 1);
  REQUIRE(image.pixels_[4][19] == 1);
  REQUIRE(image.pixels_[4][20] == 1);
  REQUIRE(image.pixels_[4][21] == 1);
  REQUIRE(image.pixels_[4][22] == 1);
  REQUIRE(image.pixels_[4][23] == 1);
  REQUIRE(image.pixels_[4][24] == 1);
  REQUIRE(image.pixels_[4][25] == 1);
  REQUIRE(image.pixels_[4][26] == 1);
  REQUIRE(image.pixels_[4][27] == 1);

  REQUIRE(image.pixels_[27][0] == 1);
  REQUIRE(image.pixels_[27][1] == 1);
  REQUIRE(image.pixels_[27][2] == 1);
  REQUIRE(image.pixels_[27][3] == 1);
  REQUIRE(image.pixels_[27][4] == 1);
  REQUIRE(image.pixels_[27][5] == 1);
  REQUIRE(image.pixels_[27][6] == 1);
  REQUIRE(image.pixels_[27][7] == 1);
  REQUIRE(image.pixels_[27][8] == 1);
  REQUIRE(image.pixels_[27][9] == 1);
  REQUIRE(image.pixels_[27][10] == 1);
  REQUIRE(image.pixels_[27][11] == 1);
  REQUIRE(image.pixels_[27][12] == 1);
  REQUIRE(image.pixels_[27][13] == 1);
  REQUIRE(image.pixels_[27][14] == 1);
  REQUIRE(image.pixels_[27][15] == 1);
  REQUIRE(image.pixels_[27][16] == 1);
  REQUIRE(image.pixels_[27][17] == 1);
  REQUIRE(image.pixels_[27][18] == 1);
  REQUIRE(image.pixels_[27][19] == 1);
  REQUIRE(image.pixels_[27][20] == 1);
  REQUIRE(image.pixels_[27][21] == 1);
  REQUIRE(image.pixels_[27][22] == 1);
  REQUIRE(image.pixels_[27][23] == 1);
  REQUIRE(image.pixels_[27][24] == 1);
  REQUIRE(image.pixels_[27][25] == 1);
  REQUIRE(image.pixels_[27][26] == 1);
  REQUIRE(image.pixels_[27][27] == 1);

}
