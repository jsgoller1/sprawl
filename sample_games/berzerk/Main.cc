#include <iostream>

// #include "Game.hh"

#define BRICK_ROWS 6
#define BRICK_COLS 8

int main() {
  Game game = Game();
  while (!(game.shouldQuit())) {
    game.getInput();
    game.update();
    game.draw();
  }
  return 0;
}
