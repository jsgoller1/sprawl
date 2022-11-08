#include "CLI.hh"
#include "InputHandler.hh"
#include "Logging.hh"
#include "Screen.hh"
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
  std::shared_ptr<World> world = wadLoader.loadWorld();
  std::shared_ptr<Screen> screen = wadLoader.loadScreen();
  std::shared_ptr<InputHandler> inputHandler = wadLoader.loadInputHandler();
  GameAction userAction = GameAction::IDLE;
  // TODO: create message queue and kick off thread for
  // running interpreter that can read input and produce commands to
  // be given to World()

  time_ms duration;
  while (userAction != QUIT) {
    duration = timer.tick();
    userAction = inputHandler->getGameAction();
    if (userAction != GameAction::IDLE) {
      LOG_DEBUG_SYS(WORLD, "GameAction: {}", userAction);
    }
    /*
    TODO: UI stuff; UI can either pause the game
    (settings menu) or not (in-game menu for "doing something"
    mid-game); pausing would mean just skipping world.update()
    */
    // uiSystem = UISystem()

    // TODO: Read from interpreter message queue until it's empty
    // and run world.update() on each action; may want to add method
    // for a batch of actions

    // TODO: We will likely want to have some kind of state detailing what to do
    // with input; e.g. if a UI menu is open, "pressing the up arrow key" should
    // not move the player around. We may also want the World/Zone to keep state
    // as well, e.g. "up" should do something different if the player is in a
    // vehicle, in combat, etc.
    world->gameLoopUpdate(userAction, duration);
    screen->drawAll(world->getDrawables());

    // If we wind up taking less time than we need should we sleep?
    // Framerates higher than 60 FPS are imperceptible, and we don't
    // want the game world moving faster than the player can handle.
    //  sleep(startTime + MS_PER_FRAME - getCurrentTime());
  }
  return 0;
}
