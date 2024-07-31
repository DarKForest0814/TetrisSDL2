#pragma once
#include "Block.h"
#include "Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstring>
#include <iostream>
#include <stdio.h>

class Renderer {
private:
  SDL_Renderer *renderer_ = NULL; // rendering instance
  SDL_Window *window_ = NULL;     // Sdl windows
  // fonts
  TTF_Font *standart; // pointer to hold location of font
  // colors SDL
  SDL_Color White = {255, 255, 255, 255};
  // UI texts
  SDL_Texture *Message;   // pointer to hold texture for text
  SDL_Texture *Message1;  // pointer to hold texture for text
  SDL_Texture *Message2;  // pointer to hold texture for text
  SDL_Texture *Highscore; // pointer to hold texture for text
  // UI sprites and textures
  SDL_Surface *board_sprite_back = NULL;    // sprite for board background
  SDL_Texture *boardTexture_back;           // texture for board background
  SDL_Surface *startScreen_sprite = NULL;   // sprite for start screen
  SDL_Texture *startScreenTexture;          // sprite for start screen
  SDL_Surface *pause_sprite = NULL;         // sprite for pause screen
  SDL_Texture *pauseTexture;                // texture for pause screen
  SDL_Surface *gameover_sprite = NULL;      // sprite for gameover screen
  SDL_Texture *gameoverTexture;             // texture for gameover screen
  SDL_Surface *gameArea_sprite_back = NULL; // sprite for board background
  SDL_Texture *gameAreaTexture_back;        // texture for board background
  // Block sprites and textures
  SDL_Surface *block_sprite_red = NULL;    // sprite for blocks
  SDL_Surface *block_sprite_green = NULL;  // sprite for blocks
  SDL_Surface *block_sprite_blue = NULL;   // sprite for blocks
  SDL_Surface *block_sprite_yellow = NULL; // sprite for blocks
  SDL_Surface *block_sprite_orange = NULL; // sprite for blocks
  SDL_Surface *block_sprite_purple = NULL; // sprite for blocks
  SDL_Surface *block_sprite_pink = NULL;   // sprite for blocks
  SDL_Texture *blockTexture_red;           // texture for block
  SDL_Texture *blockTexture_green;         // texture for block
  SDL_Texture *blockTexture_blue;          // texture for block
  SDL_Texture *blockTexture_yellow;        // texture for block
  SDL_Texture *blockTexture_orange;        // texture for block
  SDL_Texture *blockTexture_purple;        // texture for block
  SDL_Texture *blockTexture_pink;          // texture for block

  const int tile_size = 32; // size of each rectangle

  const char *title = "Tetris SDL2"; // window title

  const int width = 704;  // window height
  const int height = 704; // window width

public:
  Renderer();             // constructor for initial sdl setup
  ~Renderer();            // freeing up used memory
  void render(Game game); // function that updates the rendering buffer
  void drawBlock(Block b, int offset_x, int offset_y,
                 int alpha); // draws any given block
  void drawBoard(char Board[10][22], int offset_x, int offset_y); // draws board
  void drawText(SDL_Texture *t, const char *text, int pos_x,
                int pos_y); // draws any given text
  void clear();             // clear rendering buffer
  const char *convert_int_to_const_char(
      char *c, int i); // helper function for conversion of int to const char
  SDL_Texture *
  choose_texture(char c); // choose right texture for filled position on board
  const char *get_time(
      Game game); // puts the elapsed time since beginn into a proper format
};
