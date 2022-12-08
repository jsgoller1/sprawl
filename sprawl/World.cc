#include "World.hh"

#include "Background.hh"
#include "DrawingComponent.hh"
#include "DrawingManager.hh"
#include "GameAction.hh"
#include "GameObject.hh"
#include "InputHandler.hh"
#include "Logging.hh"
#include "PhysicsManager.hh"
#include "PositionComponent.hh"
#include "Texture.hh"

World::~World() = default;

World::World(const GraphicsSettings& graphicsSettings)
    : physicsManager(PhysicsManager()),
      drawingManager(DrawingManager(graphicsSettings)),
      gameObjects(std::vector<std::shared_ptr<GameObject>>()) {}

std::shared_ptr<Background> World::getBackground() { return this->background; }
void World::setBackground(const std::shared_ptr<Background> background) {
  this->background = background;

  // TODO: This is not good; if we update the background, we need a way to remove the previous one.
  this->drawingManager.manage(background->getIdentity().shared_from_this(),
                              getSharedPointer<PositionComponent>(background->getPositionComponent()),
                              getSharedPointer<DrawingComponent>(background->getDrawingComponent()));
  this->gameObjects.push_back(background);
}

PhysicsManager& World::getPhysicsManager() { return this->physicsManager; }
void World::setPhysicsManager(const PhysicsManager& physicsManager) {
  this->physicsManager = PhysicsManager(physicsManager);
}

void World::gameLoopUpdate(const std::shared_ptr<GameLoopInputEvents> inputEvents, const time_ms duration) {
  this->handleInput(inputEvents);
  this->physicsManager.gameLoopUpdate(duration);
  this->drawingManager.gameLoopUpdate(duration);
}

std::vector<std::shared_ptr<GameObject>>& World::getGameObjects() { return this->gameObjects; }

void World::addGameObject(const std::shared_ptr<GameObject> gameObject) {
  this->gameObjects.push_back(gameObject);
  this->physicsManager.manage(gameObject->getIdentity().shared_from_this(),
                              getSharedPointer<PhysicsComponent>(gameObject->getPhysicsComponent()),
                              getSharedPointer<PositionComponent>(gameObject->getPositionComponent()),
                              getSharedPointer<CollisionComponent>(gameObject->getCollisionComponent()));
  this->drawingManager.manage(gameObject->getIdentity().shared_from_this(),
                              getSharedPointer<PositionComponent>(gameObject->getPositionComponent()),
                              getSharedPointer<DrawingComponent>(gameObject->getDrawingComponent()));
}
