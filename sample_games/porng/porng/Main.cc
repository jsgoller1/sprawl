#include "CLI.hh"
#include "InputEvent.hh"
#include "InputHandler.hh"
#include "Logging.hh"
#include "PorngWADLoader.hh"
#include "Screen.hh"
#include "Time.hh"
#include "Types.hh"
#include "World.hh"

int main(int argc, char* argv[]) {
  CLI args(argc, argv);
  if (args.shouldQuit()) {
    return args.getReturnCode();
  }
  PorngWADLoader wadLoader = PorngWADLoader(FilePath(args.getWADDir()));
  wadLoader.loadLogging();

  Timer timer = Timer();
  bool should_quit = false;
  // TODO: Refactor world to an  class?
  std::shared_ptr<World> world = wadLoader.loadPorngWorld();
  std::shared_ptr<Screen> screen = wadLoader.loadScreen();
  std::shared_ptr<InputHandler> inputHandler = wadLoader.loadInputHandler();

  while (!should_quit) {
    time_ms duration = timer.tick();
    std::shared_ptr<GameLoopInputEvents> inputEvents = inputHandler->getGameLoopInputEvents();
    should_quit = inputEvents->getShouldQuit();
    world->gameLoopUpdate(inputEvents, duration);
    screen->drawAll(world->getDrawables());
  }
  return 0;
}