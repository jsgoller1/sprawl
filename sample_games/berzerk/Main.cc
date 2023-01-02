#include "CLI.hh"
#include "Game.hh"
#include "InputHandler.hh"
#include "Screen.hh"

int main(int argc, char* argv[]) {
  CLI args(argc, argv);
  if (args.shouldQuit()) {
    return args.getReturnCode();
  }
  InputHandler inputHandler = InputHandler();
  Screen screen = Screen(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
  Screen::ScreenDrawingProxy screenDrawingProxy = screen.getScreenDrawingProxy();

  Game game = Game(args, screenDrawingProxy);
  while (!(game.getShouldQuit() || inputHandler.shouldQuit())) {
    inputHandler.getKeyboardInput();
    game.update(inputHandler);
    game.draw(screen);
  }
}
