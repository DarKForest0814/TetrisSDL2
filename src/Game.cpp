#include "Game.h"

#include <iostream>

Game::Game(int l) {
  this->l = l;
  updateGameSpeed();
  this->s = 0;
  this->seed = int(time(0));
  srand(this->seed);
  initBoard();
  this->cBlock_ = Block();
  this->next_block = Block();
  this->pBlock_ = cBlock_;
  next_block.pos_.x = 13;
  next_block.pos_.y = 7;
  this->highScore = loadHighScore();
}

int Game::calculateScore(int k) {
  switch (k) {
  case 1:
    return 40 * (l + 1);
    break;
  case 2:
    return 100 * (l + 1);
    break;
  case 3:
    return 300 * (l + 1);
    break;
  case 4:
    return 1200 * (l + 1);
    break;
  default:
    return 0;
  }
}

void Game::updateGameSpeed() {
  switch (l) {
  case 1:
    d = 1.39;
    break;
  case 2:
    d = 1.57;
    break;
  case 3:
    d = 1.81;
    break;
  case 4:
    d = 2.14;
    break;
  case 5:
    d = 2.60;
    break;
  case 6:
    d = 3.3;
    break;
  case 7:
    d = 4.61;
    break;
  case 8:
    d = 7.5;
    break;
  case 9:
    d = 10.0;
    break;
  case 10:
    d = 12.0;
    break;
  default:
    break;
  };
  if (l >= 10 && l <= 12) {
    d = 12.0;
  } else if (l >= 13 && l <= 15) {
    d = 15.0;
  } else if (l >= 16 && l <= 18) {
    d = 20.0;
  } else if (l >= 19 && l <= 28) {
    d = 30.0;
  } else if (l >= 29) {
    d = 60.0;
  }
}
void Game::check_lines() {
  int lines_for_score = 0;
  for (int i = 0; i < 22; ++i) {
    bool line_full = true;
    for (int j = 0; j < 10; ++j) {
      if (Board[j][i] == '0') {
        line_full = false;
      }
    }
    if (line_full) {
      // level progression
      deleted_lines += 1;
      lines_for_score += 1;
      if (deleted_lines >= 10) {
        l += 1;
        deleted_lines -= 10;
        updateGameSpeed();
      }
      // repairing board and remove full line
      for (int k = i; k > 0; --k) {
        for (int g = 0; g < 10; ++g) {
          Board[g][k] = Board[g][k - 1];
        };
      }
    }
  }
  s += calculateScore(lines_for_score);
}

void Game::initBoard() {
  for (int i = 0; i < 22; ++i) {
    for (int j = 0; j < 10; ++j) {
      Board[j][i] = '0';
    }
  }
}

bool Game::is_grounded(Block b) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (b.shape_[i][j] != 1) { // checking if the block is fallid
        continue;
      };
      // floor underneath ?
      if (b.pos_.y + i + 1 >= 22) {
        return true;
      }
      // block underneath ?
      if (Board[j + b.pos_.x][i + b.pos_.y + 1] != '0') {
        return true;
      }
    }
  }
  return false;
}

bool Game::is_valid(int d) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (cBlock_.shape_[i][j] != 1) { // checking if the block is fallid
        continue;
      };
      // setting up initial color for neighbouring blocks
      char r = '0';
      char l = '0';
      // checking if neighbours are valid
      if (j + cBlock_.pos_.x + 1 < 10 && j + cBlock_.pos_.x - 1 >= 0) {
        r = Board[j + cBlock_.pos_.x + 1][i + cBlock_.pos_.y];
        l = Board[j + cBlock_.pos_.x - 1][i + cBlock_.pos_.y];
      };
      // checking if move to the right is legal
      if (d == 1) {
        if (cBlock_.pos_.x + j + 1 == 10 || r != '0') {
          return false;
        }
      }
      // checking if move to the left is legal
      if (d == 0) {
        if (cBlock_.pos_.x + j - 1 == -1 || l != '0') {
          return false;
        }
      }
    }
  }
  return true;
}

void Game::place_on_board() {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (cBlock_.shape_[i][j] != 1) { // checking if the block is fallid
        continue;
      };
      Board[j + cBlock_.pos_.x][i + cBlock_.pos_.y] = cBlock_.pos_.color;
    }
  }
}

void Game::update() {
  if (is_over || is_paused) {
    return;
  }
  if (is_grounded(cBlock_)) {
    // updating board
    place_on_board();

    // queing new blocks
    cBlock_ = next_block;
    Block b = Block();
    if (b.shape_name == cBlock_.shape_name) {
      b = Block();
    };
    next_block = b;

    // switching positions
    next_block.pos_.x = cBlock_.pos_.x;
    next_block.pos_.y = cBlock_.pos_.y;
    cBlock_.pos_.x = start_pos.x;
    cBlock_.pos_.y = start_pos.y;
    if (cBlock_.shape_name == 'I') {
      cBlock_.pos_.y -= 1;
    }
    if (is_grounded(cBlock_)) {
      is_over = true;
      if (this->highScore < this->s) {
        saveHighScore();
      }
    }

    // checking if line is full
    check_lines();
    return;
  }

  cBlock_.pos_.y += 1;
}

bool Game::is_valid_rotation(std::vector<std::vector<int>> shape) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (shape[i][j] != 1) { // checking if the block is vallid
        continue;
      };
      // setting up initial color for neighbouring blocks
      char r = '0';
      // checking if neighbours are valid
      if (j + cBlock_.pos_.x < 10 && j + cBlock_.pos_.x >= 0 &&
          i + cBlock_.pos_.y >= 0 && i + cBlock_.pos_.y < 22) {
        r = Board[j + cBlock_.pos_.x][i + cBlock_.pos_.y];
      } else {
        return false;
      }
      // checking if block is occupied
      if (r != '0') {
        return false;
      }
    }
  }
  return true;
}

int Game::loadHighScore() {
  std::ifstream file;
  std::string hs;
  file.open("../data/save_data.txt");
  if (!file) {
    std::cout << "error: Failed to load highscore from file at "
                 "../data/save_data.txt\n "
                 "     Make sure the save_data file exists!";
    return 0;
  }
  std::getline(file, hs);
  file.close();
  if (!stoi(hs)) {
    return 0;
  }
  return stoi(hs);
}

void Game::saveHighScore() {
  std::ofstream file;
  file.open("../data/save_data.txt");
  if (!file) {
    std::cout
        << "error: Failed to safe highscore to file at ../data/save_data.txt\n "
           "     Make sure the save_data file exists!";
    return;
  }
  file << s;
  file.close();
}

// Getters and setters

int Game::get_difficulty() { return this->d; }