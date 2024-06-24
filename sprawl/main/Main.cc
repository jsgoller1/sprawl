#include "ActorManager.hh"
#include "BehaviorManager.hh"
#include "CLI.hh"
#include "CollisionManager.hh"
#include "EventBusPublisher.hh"
#include "EventMessage.hh"
// #include "GraphicsManager2D.hh"
#include "GraphicsManager3D.hh"
#include "InputManager.hh"
#include "Logging.hh"
#include "PhysicsManager.hh"
#include "SystemProxy.hh"
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
  // GraphicsManager2D& graphicsManager2D = GraphicsManager2D::instance();
  GraphicsManager3D& graphicsManager3D = GraphicsManager3D::instance();
  PhysicsManager& physicsManager = PhysicsManager::instance();
  EventBusPublisher& eventBusPublisher = EventBusPublisher::instance();
  InputManager& inputManager = InputManager::instance();
  SystemProxy& systemProxy = SystemProxy::instance();

  WADLoader wadLoader = WADLoader(FilePath(args.getWADDir()));
  wadLoader.loadSettings(actorManager, behaviorManager, collisionManager, graphicsManager3D, physicsManager);
  wadLoader.loadActors(actorManager);

  Timer timer = Timer();
  bool should_quit = false;

  while (!should_quit) {
    time_ms duration = timer.tick();

    // TODO: Does order matter here? I would think we we need to test for collisions (which gives
    // game code the opportunity to respond to them), then update physics for position changes,
    // then finally draw (we want to draw the game state after the update). But it may not matter,
    // because any behavior that needs to occur will just occur on the next loop.

    inputManager.gameLoopUpdate();
    eventBusPublisher.sendMessage(GameLoopMessage());
    collisionManager.gameLoopUpdate(duration);
    physicsManager.gameLoopUpdate(duration);
    // graphicsManager2D.gameLoopUpdate(duration);
    graphicsManager3D.gameLoopUpdate(duration);

    // We quit because the programmer's code directed us to, or because it was triggered by SDL (usually
    // due to pressing the X button on the window)
    should_quit = systemProxy.getQuit() || inputManager.getQuit();
  }
  return 0;
}