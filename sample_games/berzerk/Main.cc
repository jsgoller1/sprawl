#include "CLI.hh"
#include "Game.hh"
#include "InputHandler.hh"
#include "Screen.hh"

#define DEFAULT_SCREEN_WIDTH 1200
#define DEFAULT_SCREEN_HEIGHT 800

int main(int argc, char* argv[]) {
  CLI args(argc, argv);
  if (args.shouldQuit()) {
    return args.getReturnCode();
  }
  InputHandler inputHandler = InputHandler();
  Screen screen = Screen(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);

  Game game = Game(args, screen.getScreenDrawingProxy());
  while (!(game.getShouldQuit() || inputHandler.shouldQuit())) {
    inputHandler.getKeyboardInput();
    game.update(inputHandler);
    game.draw(screen);
  }
}
