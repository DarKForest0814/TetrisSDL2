#include "Game.h"
#include <gtest/gtest.h>

TEST(is_valid, Game) {
  Game test = Game(0);
  // checking if block can move out of bounds
  if (test.cBlock_.shape_name == 'I') {
    test.cBlock_.pos_.x = 0;
  } else {
    test.cBlock_.pos_.x = -1;
  }
  ASSERT_TRUE(!(test.is_valid(0)));

  if (test.cBlock_.shape_name == 'I') {
    test.cBlock_.pos_.x = 6;
  } else {
    test.cBlock_.pos_.x = 7;
  }
  ASSERT_TRUE(!(test.is_valid(1)));

  // creating board with blocks as boarder
  for (int i = 0; i < 10; i++) {
    if (i == 0 || i == 9) {
      test.Board[i][2] = 'g';
      test.Board[i][2 + 1] = 'g';
    }
  }
  // checking if blocks can move into occupied spaces on the board
  if (test.cBlock_.shape_name == 'I') {
    test.cBlock_.pos_.x = 1;
  } else {
    test.cBlock_.pos_.x = 0;
  }
  ASSERT_TRUE(!(test.is_valid(0)));
  if (test.cBlock_.shape_name == 'I') {
    test.cBlock_.pos_.x = 5;
  } else {
    test.cBlock_.pos_.x = 6;
  }

  ASSERT_TRUE(!(test.is_valid(1)));
}

TEST(is_valid_rotation, Game) {
  // if it works for one type of block logically it must work for all of them
  Game test = Game(0);

  // makeing sure block is not O ( as O has no rotations)
  while (test.cBlock_.shape_name == 'O') {
    test.cBlock_ = Block();
  }
  // putting the block in an upright position
  test.cBlock_.shape_ = test.cBlock_.rotate(1);
  test.cBlock_.shape_ = test.cBlock_.rotate(1);
  test.cBlock_.shape_ = test.cBlock_.rotate(1);
  // checking if right valid rotation detection works
  if (test.cBlock_.shape_name == 'I') {
    test.cBlock_.pos_.x = -2;
  } else {
    test.cBlock_.pos_.x = -1;
  }
  ASSERT_TRUE(!(test.is_valid_rotation(test.cBlock_.rotate(1))));

  // checking if right valid rotation detection works
  // only L, J, T and I have free spaces on the left
  while (test.cBlock_.shape_name == 'O' || test.cBlock_.shape_name == 'Z' ||
         test.cBlock_.shape_name == 'S') {
    test.cBlock_ = Block();
  }
  // putting the block in an upright position with space on right
  test.cBlock_.shape_ = test.cBlock_.rotate(1);
  test.cBlock_.shape_ = test.cBlock_.rotate(1);

  if (test.cBlock_.shape_name == 'I') {
    test.cBlock_.pos_.x = 7;
  } else {
    test.cBlock_.pos_.x = 8;
  }
  ASSERT_TRUE(!(test.is_valid(1)));

  // creating board with blocks as boarder
  for (int i = 0; i < 10; i++) {
    if (i == 0 || i == 9) {
      test.Board[i][2] = 'g';
      test.Board[i][2 + 1] = 'g';
    }
  }
  // checking if blocks can rotate into occupied spaces on the board
  // putting the block in an upright position
  test.cBlock_.shape_ = test.cBlock_.rotate(1);
  test.cBlock_.shape_ = test.cBlock_.rotate(1);
  // checking if right valid rotation detection works
  if (test.cBlock_.shape_name == 'I') {
    test.cBlock_.pos_.x = -1;
    test.cBlock_.shape_ = test.cBlock_.rotate(1);
  } else if (test.cBlock_.shape_name == 'L') {
    test.cBlock_.shape_ = test.cBlock_.rotate(1);
  } else {
    test.cBlock_.pos_.x = 0;
  }
  ASSERT_TRUE(!(test.is_valid_rotation(test.cBlock_.rotate(1))));

  // checking if right valid rotation detection works
  // only L, J, T and I have free spaces on the left
  while (test.cBlock_.shape_name == 'O' || test.cBlock_.shape_name == 'Z' ||
         test.cBlock_.shape_name == 'S') {
    test.cBlock_ = Block();
  }
  // putting the block in an upright position with space on right
  test.cBlock_.shape_ = test.cBlock_.rotate(1);
  test.cBlock_.shape_ = test.cBlock_.rotate(1);

  if (test.cBlock_.shape_name == 'I') {
    test.cBlock_.pos_.x = 6;
  } else {
    test.cBlock_.pos_.x = 7;
  }
  ASSERT_TRUE(!(test.is_valid(1)));
}
TEST(is_grounded, Game) {
  Game test = Game(0);
  // checking if grounded when on bottom row
  test.cBlock_.pos_.y = 21;
  ASSERT_TRUE(test.is_grounded(test.cBlock_));
  // checking if is grounded if space ocupied on board
  test.cBlock_.pos_.y = 20;
  for (int i = 0; i < 10; i++) {
    test.Board[i][21] = 'g';
  }
  ASSERT_TRUE(test.is_grounded(test.cBlock_));
}
TEST(check_lines, Game) {
  Game test = Game(0);
  // test if filled lines are beeing cleared
  for (int i = 0; i < 10; i++) {
    test.Board[i][21] = 'g';
  }
  test.check_lines();
  for (int i = 0; i < 10; i++) {
    ASSERT_TRUE(test.Board[i][21] == '0');
  }
  // test if lines are moved down
  for (int i = 0; i < 10; i++) {
    test.Board[i][21] = 'g';
    if (i % 2) {
      test.Board[i][20] = 'g';
    }
  }
  test.check_lines();
  for (int i = 0; i < 10; i++) {
    if (i % 2) {
      ASSERT_TRUE(test.Board[i][21] == 'g');
    }
  }
}
TEST(place_on_board, Game) {
  // These 2 cases logically proof that any placement must work ( obviously they
  // would crash if the block would be out of bounds, which it can't ever be as
  // the is valid check has been proofen to work)
  Game test = Game(0);
  test.place_on_board();
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (test.cBlock_.shape_[i][j] != 1) { // checking if the block is fallid
        continue;
      };
      // asserting that the block hast been placed at the position relative to
      // the board
      ASSERT_TRUE(
          test.Board[j + test.cBlock_.pos_.x][i + test.cBlock_.pos_.y] ==
          test.cBlock_.pos_.color);
    }
  }
  test.cBlock_ = Block();
  test.cBlock_.pos_.y = 10;
  test.place_on_board();
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (test.cBlock_.shape_[i][j] != 1) { // checking if the block is fallid
        continue;
      };
      // asserting that the block hast been placed at the position relative to
      // the board
      ASSERT_TRUE(
          test.Board[j + test.cBlock_.pos_.x][i + test.cBlock_.pos_.y] ==
          test.cBlock_.pos_.color);
    }
  }
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}