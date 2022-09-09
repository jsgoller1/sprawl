#include "InputManager.hh"
#include "Logger.hh"
#include "Screen.hh"
#include "World.hh"

int main() {
  Screen screen = Screen();
  World world = World();
  InputManager inputManager = InputManager();
  GameAction userAction;

  while (userAction != QUIT) {
    // startTime = getCurrentTime();
    userAction = inputManager.getGameAction();
    if (userAction != GameAction::IDLE) {
      gLogger.log("GameAction: " + to_string(userAction));
    }
    // TODO:
    // uiSystem = UISystem() // ui can either pause the game
    // (settings menu) or not (in-game menu for "doing something"
    // mid-game); pausing would mean just skipping world.update()
    world.update(userAction);
    // screen.draw(world);
    // sleep(startTime + MS_PER_FRAME - getCurrentTime());
  }
}
