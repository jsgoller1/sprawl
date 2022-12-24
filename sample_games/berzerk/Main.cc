#include "Game.hh"

int main() {
  Game game = Game();
  while (!(game.getShouldQuit())) {
    game.getInput();
    game.updateLoseConditions();
    game.updateAnimations();  // probably involves something time based and selecting a texture from a sprite sheet
    game.updateAI();
    game.moveCharacters();  // according to their velocity
    game.updateCollisions();
    game.draw();
  }
}
