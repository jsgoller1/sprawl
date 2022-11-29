#include "World.hh"

// TODO: Remove this; this is just for hardcoding the screen coordinates for
// loadHardcoded(); World should NOT know about Screen.
#include "Screen.hh"

World::~World() = default;

World::World() {
  this->physicsManager = std::shared_ptr<PhysicsManager>(new PhysicsManager());
  this->gameObjects =
      std::shared_ptr<std::vector<std::shared_ptr<GameObject>>>(new std::vector<std::shared_ptr<GameObject>>());
}

std::shared_ptr<Background> World::getBackground() const { return this->background; }
void World::setBackground(const std::shared_ptr<Background> background) { this->background = background; }

std::shared_ptr<PhysicsManager> World::getPhysicsManager() const { return this->physicsManager; }
void World::setPhysicsManager(const std::shared_ptr<PhysicsManager> physicsManager) {
  this->physicsManager = physicsManager;
}

void World::gameLoopUpdate(const std::shared_ptr<GameLoopInputEvents> inputEvents, const time_ms duration) {
  this->handleInput(inputEvents);
  this->physicsManager->gameLoopUpdate(duration);
}

std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> World::getGameObjects() const { return this->gameObjects; }
void World::setGameObjects(const std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects) {
  this->gameObjects = gameObjects;
}

void World::addGameObject(const std::shared_ptr<GameObject> gameObject) {
  this->gameObjects->push_back(gameObject);
  if (gameObject->getPhysicsComponent() != nullptr) {
    this->physicsManager->manage(gameObject->getIdentity(), gameObject->getPhysicsComponent(),
                                 gameObject->getPositionComponent(), gameObject->getCollisionComponent());
  }
}
