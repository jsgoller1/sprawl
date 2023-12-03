#include "PhysicsManager.hh"

#include "Assumption.hh"
#include "PhysicsComponent.hh"

PhysicsManager::PhysicsManager() = default;
PhysicsManager::~PhysicsManager() = default;

real PhysicsManager::getGravityConstant() const { return this->gravityConstant; }
void PhysicsManager::setGravityConstant(const real gravityConstant) { this->gravityConstant = gravityConstant; }

void PhysicsManager::gameLoopUpdate(const time_ms duration) {
  std::unordered_set<std::shared_ptr<Actor>> collisionCandidates;
  for (std::shared_ptr<Actor> actor : this->managedActors) {
    std::string actorString = actor->toString();
    std::shared_ptr<PositionComponent> positionComponent = actor->getComponent<PositionComponent>();
    std::shared_ptr<PhysicsComponent> physicsComponent = actor->getComponent<PhysicsComponent>();
    std::shared_ptr<CollisionComponent> collisionComponent = actor->getComponent<CollisionComponent>();
    if (!positionComponent || !physicsComponent || !collisionComponent) {
      LOG_DEBUG_SYS(PHYSICS, "Skipping actor without position, physics, or collision component: {}", actorString);
      continue;
    }

    LOG_DEBUG_SYS(PHYSICS, "Physics update beginning: {}", actorString);
    LOG_DEBUG_SYS(PHYSICS, "Position: {}", positionComponent->getCenter().to_string());

    if (!(physicsComponent->gravityEnabled())) {
      LOG_DEBUG_SYS(PHYSICS, "Skipping gravity: {}", actorString);
    } else {
      physicsComponent->applyGravity(this->gravityConstant);
      LOG_DEBUG_SYS(PHYSICS, "Applying gravity: {}", actorString);
    }
    Vect2D positionDelta = physicsComponent->integrate(duration);
    if (positionDelta == Vect2D::zero()) {
      LOG_DEBUG_SYS(PHYSICS, "No movement, collisions skipped: {}", actorString);
    } else {
      LOG_DEBUG_SYS(PHYSICS, "{} attempting movement {}", actorString, positionDelta.to_string());

      Vect2D finalPosition = positionComponent->getCenter() + positionDelta;
      positionComponent->setCenter(finalPosition);
    }
    LOG_DEBUG_SYS(PHYSICS, "Physics update completed: {}", actorString);
  }
}
