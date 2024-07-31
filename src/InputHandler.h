#pragma once
#include <SDL2/SDL.h>

#include "Game.h"

class InputHandler {
private:
  int rl;
  int rr;

public:
  InputHandler(int rr, int rl);                  // constructor for InputHandler
  void handleInput(SDL_Event event, Game &game); // handle input
};