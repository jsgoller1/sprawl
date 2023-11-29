#include "ActorManager.hh"
#include "BehaviorManager.hh"
#include "CLI.hh"
#include "CollisionManager.hh"
#include "DrawingManager.hh"
#include "InputEvent.hh"
#include "InputHandler.hh"
#include "Logging.hh"
#include "PhysicsManager.hh"
#include "Time.hh"
#include "Types.hh"
#include "WADLoader.hh"

int main(int argc, char* argv[]) {
  CLI args(argc, argv);
  if (args.shouldQuit()) {
    return args.getReturnCode();
  }

  ActorManager& actorManager = ActorManager::instance();
  BehaviorManager& behaviorManager = BehaviorManager::instance();
  CollisionManager& collisionManager = CollisionManager::instance();
  DrawingManager& drawingManager = DrawingManager::instance();
  PhysicsManager& physicsManager = PhysicsManager::instance();

  WADLoader wadLoader = WADLoader(FilePath(args.getWADDir()));
  wadLoader.loadSettings(actorManager, behaviorManager, collisionManager, drawingManager, physicsManager);
  wadLoader.loadActors(actorManager);
  wadLoader.loadLogging();

  Timer timer = Timer();
  bool should_quit = false;
  std::shared_ptr<InputHandler> inputHandler = wadLoader.loadInputHandler();

  while (!should_quit) {
    time_ms duration = timer.tick();
    std::shared_ptr<GameLoopInputEvents> inputEvents = inputHandler->getGameLoopInputEvents();
    should_quit = inputEvents->getShouldQuit();

    // Order is important here: we need to test for collisions (which gives
    // game code the opportunity to respond to them), then update physics for position changes,
    // then finally draw. This is because we want to draw the game state after the update.
    collisionManager.gameLoopUpdate(duration);
    physicsManager.gameLoopUpdate(duration);
    drawingManager.gameLoopUpdate(duration);
  }
  return 0;
}
