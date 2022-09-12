#include "InputHandler.hh"
#include "Logger.hh"
#include "Screen.hh"
#include "World.hh"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

int main() {
  Screen screen = Screen(SCREEN_WIDTH, SCREEN_HEIGHT);
  World world = World();
  InputHandler inputManager = InputHandler();
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
    screen.drawAll(world.getDrawables());
    // sleep(startTime + MS_PER_FRAME - getCurrentTime());
  }
}
