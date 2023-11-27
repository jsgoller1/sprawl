#include "World.hh"

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

PhysicsManager& World::getPhysicsManager() { return this->physicsManager; }
void World::setPhysicsManager(const PhysicsManager& physicsManager) {
  this->physicsManager = PhysicsManager(physicsManager);
}

void World::gameLoopUpdate(const time_ms duration) {
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
