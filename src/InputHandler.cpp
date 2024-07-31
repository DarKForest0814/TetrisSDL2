#include "InputHandler.h"

InputHandler::InputHandler(int rr, int rl) {
  this->rr = rr;
  this->rl = rl;
}

void InputHandler::handleInput(SDL_Event event, Game &game) {
  std::vector<std::vector<int>> rshape;
  switch (event.type) {
  /* Look for a keypress */
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_s:
      if (!game.is_over && !game.is_paused) {
        if (!game.is_grounded(game.cBlock_)) {
          game.cBlock_.pos_.y += 1;
          game.s++;
        }
      }
      break;
    case SDLK_d:
      if (!game.is_over && !game.is_paused) {
        if (game.is_valid(1) && !game.is_grounded(game.cBlock_)) {
          game.cBlock_.pos_.x += 1;
        }
      }
      break;
    case SDLK_a:
      if (!game.is_over && !game.is_paused) {
        if (game.is_valid(0) && !game.is_grounded(game.cBlock_)) {
          game.cBlock_.pos_.x -= 1;
        };
      }
      break;
    case SDLK_SPACE:
      if (!game.is_started) {
        game.is_started = true;
        game.start = time(0);
        break;
      }
      if (game.is_paused && !game.is_over) {
        game.is_paused = false;
      } else if (!game.is_paused && !game.is_over) {
        game.is_paused = true;
      } else if (game.is_over) {
        game = Game(0);
      }
      break;
    };
  };

  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == rl) {
      std::cout << "Key: " << event.key.keysym.sym;
      if (!game.is_over && !game.is_paused && game.cBlock_.shape_name != 'O') {
        rshape = game.cBlock_.rotate(0); // rotation left
        if (game.is_valid_rotation(rshape) && !game.is_grounded(game.cBlock_)) {
          game.cBlock_.shape_ = rshape;
        };
      }
    } else if (event.key.keysym.sym == rr) {
      std::cout << "Key: " << event.key.keysym.sym;
      if (!game.is_over && !game.is_paused && game.cBlock_.shape_name != 'O') {
        rshape = game.cBlock_.rotate(1); // rotation right
        if (game.is_valid_rotation(rshape) && !game.is_grounded(game.cBlock_)) {
          game.cBlock_.shape_ = rshape;
        };
      }
    }
  }
}