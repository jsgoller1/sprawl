#include <iostream>

#include "Game.hh"

int main() {
  Game game = Game();
  while (!(game.shouldQuit())) {
    game.getInput();
    game.update();
    game.draw();
  }
  return 0;
}
