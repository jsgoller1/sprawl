#include "CLI.hh"
#include "Game.hh"
#include "InputHandler.hh"
#include "Screen.hh"
#include "Time.hh"

int main(int argc, char* argv[]) {
  CLI args(argc, argv);
  if (args.shouldQuit()) {
    return args.getReturnCode();
  }
  InputHandler inputHandler = InputHandler();
  Screen screen = Screen(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
  Screen::ScreenDrawingProxy screenDrawingProxy = screen.getScreenDrawingProxy();
  Timer timer = Timer();

  Game game = Game(args, screenDrawingProxy);
  while (!(game.getShouldQuit() || inputHandler.shouldQuit())) {
    time_ms deltaT = timer.tick();
    inputHandler.getKeyboardInput();
    game.update(inputHandler, deltaT);
    game.draw(screen);
  }
}
