#include "InputHandler.hh"
#include "Logger.hh"
#include "Screen.hh"
#include "World.hh"

int main() {
  Screen screen = Screen(SCREEN_WIDTH, SCREEN_HEIGHT);
  World world = World();
  InputHandler inputManager = InputHandler();
  GameAction userAction;
  // TODO: create message queue and kick off thread for
  // running interpreter that can read input and produce commands to
  // be given to World()

  while (userAction != QUIT) {
    // startTime = getCurrentTime();
    userAction = inputManager.getGameAction();
    if (userAction != GameAction::IDLE) {
      log("GameAction: " + to_string(userAction));
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

    world.update(userAction);
    screen.drawAll(world.getDrawables());
    // sleep(startTime + MS_PER_FRAME - getCurrentTime());

    // log("Quitting after one loop.");
    // return 0;
  }
}
