#include "Game.h"
#include "InputHandler.h"
#include "Renderer.h"

#include <iostream>

using namespace std;

int main(int argc, const char **argv) {
  bool quit = false;
  SDL_Event event;

  // initializing requiered instances
  cout << "info: Initializing Renderer " << endl;
  Renderer renderer = Renderer();
  cout << "info: Initializing InputHandler " << endl;
  InputHandler handler =
      InputHandler(argc > 2 ? static_cast<int>(argv[2][0]) : 101,
                   argc > 3 ? static_cast<int>(argv[3][0]) : 113);
  cout << "info: Initializing Game Instance " << endl;
  Game game = Game(argc > 1 ? atoi(argv[1]) : 0);

  // variables for calculation of tick rate  ( update rate)
  unsigned int b = SDL_GetTicks();
  unsigned int c = SDL_GetTicks();
  double delta = 0;

  cout << "info: Starting main loop" << endl;
  // gameloop
  while (!quit) {

    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
      quit = true;
      break;
    }

    // input
    handler.handleInput(event, game);

    b = SDL_GetTicks();
    delta = b - c;
    if (delta > 1000 / game.d) {
      cout << "info: UPDATE_CAP = " << 1000 / delta << endl;

      c = b;

      // update
      game.update();

      delta = 0;
    }
    // render
    renderer.render(game);
    renderer.clear();
  }
  return 0;
}