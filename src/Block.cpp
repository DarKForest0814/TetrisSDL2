#include "Block.h"
#include <cstdlib>
#include <ctime>

Block::Block() {
  // generating random shape for block
  int blocktype = rand() % 7;

  switch (blocktype) {
  case 0:
    this->shape_ = {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}};
    this->pos_ = {pos_.x, pos_.y, 'i'}; // pink
    this->shape_name = 'I';
    break;
  case 1:
    this->shape_ = {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}};
    this->pos_ = {pos_.x, pos_.y, 'r'}; // red
    this->shape_name = 'J';
    break;
  case 2:
    this->shape_ = {{0, 0, 0, 0}, {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}};
    this->pos_ = {pos_.x, pos_.y, 'y'}; // yellow
    this->shape_name = 'L';
    break;
  case 3:
    this->shape_ = {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};
    this->pos_ = {pos_.x, pos_.y, 'p'}; // purple
    this->shape_name = 'O';
    break;
  case 4:
    this->shape_ = {{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}};
    this->pos_ = {pos_.x, pos_.y, 'o'}; // orange
    this->shape_name = 'S';
    break;
  case 5:
    this->shape_ = {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}};
    this->pos_ = {pos_.x, pos_.y, 'b'}; // blue
    this->shape_name = 'T';
    break;
  case 6:
    this->shape_ = {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};
    this->pos_ = {pos_.x, pos_.y, 'g'}; // green
    this->shape_name = 'Z';
    break;
  default:
    break;
  };
  // making sure the I block is allined right
  if (shape_name == 'I') {
    pos_.y -= 1;
  }
}

std::vector<std::vector<int>> Block::rotate(int d) {
  std::vector<std::vector<int>> shape;
  switch (this->shape_name) {
  case 'I':
    switch (this->current_rotation) {
    case 0:
      shape = {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}};
      this->current_rotation = 1;
      break;
    case 1:
      shape = {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}};
      this->current_rotation = 0;
      break;
    }
    break;
  case 'Z':
    switch (this->current_rotation) {
    case 0:
      shape = {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}};
      this->current_rotation = 1;
      break;
    case 1:
      shape = {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};
      this->current_rotation = 0;
      break;
    }
    break;
  case 'T':
    switch (this->current_rotation) {
    case 0:
      if (d == 1) { // right
        shape = {{0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}};
        this->current_rotation = 1;
      } else if (d == 0) { // left
        shape = {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}};
        this->current_rotation = 3;
      }
      break;
    case 1:
      if (d == 1) { // right
        shape = {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        this->current_rotation = 2;
      } else if (d == 0) { // left
        shape = {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}};
        this->current_rotation = 0;
      }
      break;
    case 2:
      if (d == 1) { // right
        shape = {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}};
        this->current_rotation = 3;
      } else if (d == 0) { // left
        shape = {{0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}};
        this->current_rotation = 1;
      }
      break;
    case 3:
      if (d == 1) { // right
        shape = {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}};
        this->current_rotation = 0;
      } else if (d == 0) { // left
        shape = {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        this->current_rotation = 2;
      }
      break;
    }
    break;
  case 'S':
    switch (this->current_rotation) {
    case 0:
      shape = {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}};
      this->current_rotation = 1;
      break;
    case 1:
      shape = {{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}};
      this->current_rotation = 0;
      break;
    }
    break;
  case 'J':
    switch (this->current_rotation) {
    case 0:
      if (d == 1) { // right
        shape = {{0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}};
        this->current_rotation = 1;
      } else if (d == 0) { // left
        shape = {{0, 1, 1, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}};
        this->current_rotation = 3;
      }
      break;
    case 1:
      if (d == 1) { // right
        shape = {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        this->current_rotation = 2;
      } else if (d == 0) { // left
        shape = {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}};
        this->current_rotation = 0;
      }
      break;
    case 2:
      if (d == 1) { // right
        shape = {{0, 1, 1, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}};
        this->current_rotation = 3;
      } else if (d == 0) { // left
        shape = {{0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}};
        this->current_rotation = 1;
      }
      break;
    case 3:
      if (d == 1) { // right
        shape = {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}};
        this->current_rotation = 0;
      } else if (d == 0) { // left
        shape = {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        this->current_rotation = 2;
      }
      break;
    }
    break;
  case 'L':
    switch (this->current_rotation) {
    case 0:
      if (d == 1) { // right
        shape = {{1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}};
        this->current_rotation = 1;
      } else if (d == 0) { // left
        shape = {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};
        this->current_rotation = 3;
      }
      break;
    case 1:
      if (d == 1) { // right
        shape = {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        this->current_rotation = 2;
      } else if (d == 0) { // left
        shape = {{0, 0, 0, 0}, {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}};
        this->current_rotation = 0;
      }
      break;
    case 2:
      if (d == 1) { // right
        shape = {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};
        this->current_rotation = 3;
      } else if (d == 0) { // left
        shape = {{1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}};
        this->current_rotation = 1;
      }
      break;
    case 3:
      if (d == 1) { // right
        shape = {{0, 0, 0, 0}, {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}};
        this->current_rotation = 0;
      } else if (d == 0) { // left
        shape = {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        this->current_rotation = 2;
      }
      break;
    }
    break;
  default:
    break;
  }
  return shape;
}

// getters and setters

const Position Block::get_pos() { return this->pos_; }