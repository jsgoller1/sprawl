#include "CLI.hh"
#include "InputEvent.hh"
#include "InputHandler.hh"
#include "Logging.hh"
#include "Time.hh"
#include "Types.hh"
#include "WADLoader.hh"
#include "World.hh"

int main(int argc, char* argv[]) {
  CLI args(argc, argv);
  if (args.shouldQuit()) {
    return args.getReturnCode();
  }
  WADLoader wadLoader = WADLoader(FilePath(args.getWADDir()));
  wadLoader.loadLogging();

  Timer timer = Timer();
  bool should_quit = false;
  std::shared_ptr<World> world = wadLoader.loadWorld();
  std::shared_ptr<InputHandler> inputHandler = wadLoader.loadInputHandler();

  while (!should_quit) {
    time_ms duration = timer.tick();
    std::shared_ptr<GameLoopInputEvents> inputEvents = inputHandler->getGameLoopInputEvents();
    should_quit = inputEvents->getShouldQuit();
    world->gameLoopUpdate(duration);
  }
  return 0;
}
