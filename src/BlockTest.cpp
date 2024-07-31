#include "Block.h"
#include <cmath>
#include <gtest/gtest.h>

TEST(BlockGeneration, Block) {
  Block blocks[1000];
  int num_shapes[7];
  for (int i = 0; i < 1000; ++i) {
    blocks[i] = Block();
    switch (blocks[i].shape_name) {
    case 'I':
      num_shapes[0] += 1;
      break;
    case 'J':
      num_shapes[1] += 1;
      break;
    case 'L':
      num_shapes[2] += 1;
      break;
    case 'O':
      num_shapes[3] += 1;
      break;
    case 'S':
      num_shapes[4] += 1;
      break;
    case 'T':
      num_shapes[5] += 1;
      break;
    case 'Z':
      num_shapes[6] += 1;
      break;
    default:
      break;
    }
  }
  bool isRandom = true;
  double expectedFrequency = 1000 / 7.0;
  double variance = 0.0;
  for (int i = 0; i < 7; ++i) {
    variance += (num_shapes[i] - expectedFrequency) *
                (num_shapes[i] - expectedFrequency);
  }
  variance /= 7;
  double standardDeviation = std::sqrt(variance);
  for (int i = 0; i < 7; ++i) {
    double deviation = std::abs(num_shapes[i] - expectedFrequency);
    // std::cout << num_shapes[i] << " Abweichung für " << (i + 1) << ": "
    //           << deviation;
    if (deviation > 2 * standardDeviation) {
      // std::cout << " (nicht zufällig!)"<< std::endl;
      isRandom = false;
    }
  }
  ASSERT_TRUE(isRandom);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}