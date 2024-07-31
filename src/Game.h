#pragma once
#include "Block.h"
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Game {
private:
  int seed;              // randomnes seed
  int deleted_lines = 0; // keeping track of deleted lines

public:
  Block cBlock_;      // current block
  Block pBlock_;      // preview block
  Block next_block;   // preloading next block
  char Board[10][22]; // state of board
  int board_x = 2;    // board offset x
  int board_y = -1;   // board offset y

  int highScore = 0; // keeping track of current highscore

  time_t start; // start of game time

  bool is_over = false;    // keeping track of gameover
  bool is_paused = true;   // keeping track of pause
  bool is_started = false; // keeping track of start

  int l;          // current lvl
  int s;          // current score
  float d = 1.25; // current difficulty/speed

  Game(int l);          // initializes game state
  void initBoard();     // initializing board
  void update();        // updates game state
  bool is_valid(int d); // checking for illegal moves
  bool is_valid_rotation(
      std::vector<std::vector<int>> shape); // checking if rotation is valid
  bool is_grounded(Block b);                // checks if block hit bottom
  void place_on_board();                    // places block on board
  void check_lines();                       // checking if line is full
  void updateGameSpeed(); // updating game speed corresponding to current level
  int calculateScore(int k); // calculating score

  int loadHighScore();  // loading highscore from file
  void saveHighScore(); // safeing highscore to file

  // getters and setters
  int get_difficulty(); // returns current difficulty multiplyer

  FRIEND_TEST(is_valid_checks, Game);
};