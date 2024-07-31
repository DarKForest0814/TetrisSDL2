#pragma once

#include <gtest/gtest.h>

// simple structure to hold positional values on board and color of block for
// rendering
struct Position {
  int x, y;
  char color;
};

const Position start_pos{3, 1, '0'}; // starting position in grid

class Block {
private:
  int current_rotation = 0; // stores current rotational state of block
public:
  Position pos_ = start_pos;            // setting up starting pos in grid
  std::vector<std::vector<int>> shape_; // holds blocktype (shape)
  char shape_name; // stores name of shape for debugging purposes

  Block(); // constructor block

  void move();                                 // moves a block
  std::vector<std::vector<int>> rotate(int d); // rotates a block

  // getters and setters
  const Position get_pos(); // returns current position

  FRIEND_TEST(BlockGeneration, Block);
};