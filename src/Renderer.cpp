#include "Renderer.h"

#include <iostream>
#include <vector>

Renderer::Renderer() {
  // Initializing SDL and error handeling

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "error: Failed to initialize SDL2! SDL_Error: "
              << SDL_GetError() << std::endl;
    return;
  }

  this->window_ = SDL_CreateWindow(this->title, 100, 100, this->width,
                                   this->height, SDL_WINDOW_SHOWN);
  if (this->window_ == nullptr) {
    std::cerr << "error: Failed to create SDL2 window! SDL_Error: "
              << SDL_GetError() << std::endl;
    SDL_Quit();
    return;
  }
  // fixes window size to width and height
  SDL_SetWindowResizable(this->window_, false);

  this->renderer_ =
      SDL_CreateRenderer(this->window_, -1, SDL_RENDERER_ACCELERATED);
  if (this->renderer_ == nullptr) {
    std::cerr << "error: Failed to create SDL2 renderer! SDL_Error: "
              << SDL_GetError() << std::endl;
    SDL_DestroyWindow(this->window_);
    SDL_Quit();
    return;
  }
  // Initializing font
  TTF_Init();
  // loading fonts
  this->standart = TTF_OpenFont("../res/standart.ttf", 24);
  if (this->standart == NULL) {
    fprintf(stderr, "error: font not found\n");
    exit(EXIT_FAILURE);
  }
  // loading images to sprites
  this->startScreen_sprite = IMG_Load("../res/start.png");
  this->block_sprite_green = IMG_Load("../res/block_green.png");
  this->block_sprite_pink = IMG_Load("../res/block_pink.png");
  this->block_sprite_purple = IMG_Load("../res/block_purple.png");
  this->block_sprite_blue = IMG_Load("../res/block_blue.png");
  this->block_sprite_red = IMG_Load("../res/block_red.png");
  this->block_sprite_orange = IMG_Load("../res/block_orange.png");
  this->block_sprite_yellow = IMG_Load("../res/block_yellow.png");
  this->board_sprite_back = IMG_Load("../res/board_back.png");
  this->gameArea_sprite_back = IMG_Load("../res/game_back.png");
  this->gameover_sprite = IMG_Load("../res/gameover.png");
  this->pause_sprite = IMG_Load("../res/paused.png");
  // loading to textures
  this->startScreenTexture =
      SDL_CreateTextureFromSurface(this->renderer_, this->startScreen_sprite);
  this->boardTexture_back =
      SDL_CreateTextureFromSurface(this->renderer_, this->board_sprite_back);
  this->gameoverTexture =
      SDL_CreateTextureFromSurface(this->renderer_, this->gameover_sprite);
  this->pauseTexture =
      SDL_CreateTextureFromSurface(this->renderer_, this->pause_sprite);
  this->gameAreaTexture_back =
      SDL_CreateTextureFromSurface(this->renderer_, this->gameArea_sprite_back);
  this->blockTexture_yellow =
      SDL_CreateTextureFromSurface(this->renderer_, this->block_sprite_yellow);
  this->blockTexture_green =
      SDL_CreateTextureFromSurface(this->renderer_, this->block_sprite_green);
  this->blockTexture_pink =
      SDL_CreateTextureFromSurface(this->renderer_, this->block_sprite_pink);
  this->blockTexture_purple =
      SDL_CreateTextureFromSurface(this->renderer_, this->block_sprite_purple);
  this->blockTexture_red =
      SDL_CreateTextureFromSurface(this->renderer_, this->block_sprite_red);
  this->blockTexture_blue =
      SDL_CreateTextureFromSurface(this->renderer_, this->block_sprite_blue);
  this->blockTexture_orange =
      SDL_CreateTextureFromSurface(this->renderer_, this->block_sprite_orange);
  // freeing up no longer needed images
  SDL_FreeSurface(this->startScreen_sprite);
  SDL_FreeSurface(this->gameArea_sprite_back);
  SDL_FreeSurface(this->pause_sprite);
  SDL_FreeSurface(this->gameover_sprite);
  SDL_FreeSurface(this->board_sprite_back);
  SDL_FreeSurface(this->block_sprite_yellow);
  SDL_FreeSurface(this->block_sprite_pink);
  SDL_FreeSurface(this->block_sprite_purple);
  SDL_FreeSurface(this->block_sprite_blue);
  SDL_FreeSurface(this->block_sprite_red);
  SDL_FreeSurface(this->block_sprite_orange);
  SDL_FreeSurface(this->block_sprite_green);
}

void Renderer::drawText(SDL_Texture *t, const char *text, int pos_x,
                        int pos_y) {
  SDL_Surface *s = TTF_RenderText_Solid(this->standart, text, this->White);
  // convert into texture
  t = SDL_CreateTextureFromSurface(this->renderer_, s);

  // create a rect
  SDL_Rect Message_rect;
  Message_rect.x = pos_x;
  Message_rect.y = pos_y;
  Message_rect.w = s->w;
  Message_rect.h = s->h;

  // freeing surface
  SDL_FreeSurface(s);

  // copying texture to rendering buffer
  SDL_RenderCopy(this->renderer_, t, NULL, &Message_rect);
  SDL_DestroyTexture(t);
}

const char *Renderer::get_time(Game game) {
  double seconds_since_start = difftime(time(0), game.start);
  // storing seconds and minuts as ints
  int sec = (int)(seconds_since_start) % 60;
  int min = (int)(seconds_since_start - sec) / 60;
  // strings to hold seconds and minuts
  char secStr[32];
  char minStr[32];
  char time[20] = "TIME: ";
  // putting everythin together
  std::sprintf(minStr, "%d", min);
  std::sprintf(secStr, "%d", sec);
  std::strcat(time, minStr);
  std::strcat(time, ":");
  // adding a 0 to the seconds if smaller than 10 for estatic reasons
  if (sec < 10) {
    std::strcat(time, "0");
  }
  std::strcat(time, secStr);
  const char *r = time;
  return r;
}

const char *Renderer::convert_int_to_const_char(char *c, int i) {
  // string to hold int
  char intStr[32];
  // putting everything together
  std::sprintf(intStr, "%d", i);
  std::strcat(c, intStr);
  const char *r = c;
  return r;
}

void Renderer::render(Game game) {
  drawBoard(game.Board, game.board_x, game.board_y);
  drawBlock(game.cBlock_, game.board_x, game.board_y, 255);
  // preview block
  game.pBlock_ = game.cBlock_;
  while (!game.is_grounded(game.pBlock_)) {
    game.pBlock_.pos_.y += 1;
  }
  drawBlock(game.pBlock_, game.board_x, game.board_y, 100);
  drawBlock(game.next_block, game.board_x, game.board_y, 255);

  char score[20] = "SCORE: ";
  char level[20] = "LEVEL: ";
  char hs[20] = "";
  if (game.is_started) {
    drawText(Message, convert_int_to_const_char(score, game.s),
             tile_size * 15 - 16, tile_size * 14 + 4);
    drawText(Message1, convert_int_to_const_char(level, game.l),
             tile_size * 15 - 16, tile_size * 16 + 4);
    drawText(Message2, get_time(game), tile_size * 15 - 16, tile_size * 18 + 4);
    drawText(Highscore, convert_int_to_const_char(hs, game.highScore),
             tile_size * 15 + 24, tile_size * 12);
  }
  if (game.is_over) {
    // drawing gameover
    SDL_Rect over;
    over.x = 0;
    over.y = 0;
    over.w = this->width;
    over.h = this->height;
    SDL_RenderCopy(this->renderer_, gameoverTexture, NULL, &over);

  } else if (game.is_paused && game.is_started) {
    // drawing pause screen
    SDL_Rect pause;
    pause.x = 0;
    pause.y = 0;
    pause.w = this->width;
    pause.h = this->height;
    SDL_RenderCopy(this->renderer_, pauseTexture, NULL, &pause);
  } else if (!game.is_started) {
    // drawing start screen
    SDL_Rect start;
    start.x = 0;
    start.y = 0;
    start.w = this->width;
    start.h = this->height;
    SDL_RenderCopy(this->renderer_, startScreenTexture, NULL, &start);
  }
  SDL_RenderPresent(this->renderer_);
}

SDL_Texture *Renderer::choose_texture(char c) {
  switch (c) {
  case 'b':
    return this->blockTexture_blue;
  case 'r':
    return this->blockTexture_red;
  case 'i':
    return this->blockTexture_pink;
  case 'g':
    return this->blockTexture_green;
  case 'y':
    return this->blockTexture_yellow;
  case 'o':
    return this->blockTexture_orange;
  case 'p':
    return this->blockTexture_purple;
  default:
    return this->blockTexture_red;
  };
}

void Renderer::drawBoard(char Board[10][22], int offset_x, int offset_y) {
  // drawing game area
  SDL_Rect back;
  back.x = 0;
  back.y = 0;
  back.w = this->width;
  back.h = this->height;
  SDL_RenderCopy(this->renderer_, gameAreaTexture_back, NULL, &back);
  for (int i = 2; i < 22; ++i) {
    for (int j = 0; j < 10; ++j) {
      SDL_Rect rect;
      // drawing background
      rect.x = (1 * j * tile_size) + (offset_x * tile_size);
      rect.y = (1 * i * tile_size) + (offset_y * tile_size);
      rect.w = tile_size;
      rect.h = tile_size;
      SDL_RenderCopy(this->renderer_, boardTexture_back, NULL, &rect);

      if (Board[j][i] != '0') {
        // drawing empty block in board
        rect.x = (1 * j * tile_size) + (offset_x * tile_size);
        rect.y = (1 * i * tile_size) + (offset_y * tile_size);
        ;
        rect.w = tile_size;
        rect.h = tile_size;
        SDL_SetTextureAlphaMod(choose_texture(Board[j][i]), 255);
        SDL_RenderCopy(this->renderer_, choose_texture(Board[j][i]), NULL,
                       &rect);
      }
    }
  }
}

void Renderer::drawBlock(Block b, int offset_x, int offset_y, int alpha) {
  for (int i = 0; i < 4; ++i) {
    std::vector<int> a = b.shape_[i];
    for (int j = 0; j < 4; ++j) {
      // offset by current position
      SDL_Rect rect;
      // check if block is valid and in the playing field
      if (a[j] == 1 && b.get_pos().y + i > 1) {
        rect.x = (b.get_pos().x * tile_size) + (j * tile_size) +
                 (offset_x * tile_size);
        rect.y = (b.get_pos().y * tile_size) + (i * tile_size) +
                 (offset_y * tile_size);
        rect.w = tile_size;
        rect.h = tile_size;
        SDL_SetTextureAlphaMod(choose_texture(b.get_pos().color), alpha);
        SDL_RenderCopy(this->renderer_, choose_texture(b.get_pos().color), NULL,
                       &rect);
      }
    }
  }
}

Renderer::~Renderer() {
  // Cleaning up textures
  SDL_DestroyTexture(startScreenTexture);
  SDL_DestroyTexture(pauseTexture);
  SDL_DestroyTexture(gameoverTexture);
  SDL_DestroyTexture(Message);
  SDL_DestroyTexture(Message1);
  SDL_DestroyTexture(Message2);
  SDL_DestroyTexture(Highscore);
  SDL_DestroyTexture(gameAreaTexture_back);
  SDL_DestroyTexture(boardTexture_back);
  SDL_DestroyTexture(blockTexture_red);
  SDL_DestroyTexture(blockTexture_green);
  SDL_DestroyTexture(blockTexture_blue);
  SDL_DestroyTexture(blockTexture_yellow);
  SDL_DestroyTexture(blockTexture_orange);
  SDL_DestroyTexture(blockTexture_purple);
  SDL_DestroyTexture(blockTexture_pink);
  // closing font
  TTF_CloseFont(this->standart);
  TTF_Quit();
  // Destroy Renderer instance
  SDL_DestroyRenderer(this->renderer_);

  // Destroy the window created above
  SDL_DestroyWindow(this->window_);

  IMG_Quit();
  SDL_Quit();
  std::cout << "info: Renderer finished clean up\n";
}

void Renderer::clear() { SDL_RenderClear(this->renderer_); }