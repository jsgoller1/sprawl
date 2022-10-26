
#pragma once

#include "GameAction.hh"
#include "GameObject.hh"
#include "Logging.hh"
#include "Memory.hh"
#include "PhysicsComponent.hh"
#include "PositionComponent.hh"
#include "Types.hh"

class Character : public GameObject {
  // Self explanatory: parent class for player, npcs, enemies, etc
 public:
  Character(const shared_ptr<GameObjectID> gameObjectID,
            const shared_ptr<PositionComponent> positionComponent,
            const shared_ptr<PhysicsComponent> physicsComponent = nullptr,
            const shared_ptr<DrawingComponent> drawingComponent = nullptr);
  void move(const GameAction& action);
  void jump();

 private:
  // TODO: These are getting scrapped, not going to write accessors.
  shared_ptr<Point> moveSpeed;
  int jumpCount;
};
