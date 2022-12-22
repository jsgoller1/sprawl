
#pragma once

#include "CharacterPhysicsComponent.hh"
#include "GameAction.hh"
#include "GameObject.hh"
#include "Logging.hh"
#include "PhysicsComponent.hh"
#include "PositionComponent.hh"
#include "Types.hh"

class Character : public GameObject {
  /*
   * Characters are actual characters in the game, both the player character
   * (PC) and non-player characters (NPCs)
   */
 public:
  Character(const EntityName name = EntityName(""),
            const std::shared_ptr<PositionComponent> positionComponent = nullptr,
            const std::shared_ptr<CollisionComponent> collisionComponent = nullptr,
            const std::shared_ptr<CharacterPhysicsComponent> cphysicsComponent = nullptr,
            const std::shared_ptr<DrawingComponent> drawingComponent = nullptr);
  void move(const GameAction& action);
  void jump();

  CharacterPhysicsComponent& getPhysicsComponent() const override;

 private:
  std::shared_ptr<CharacterPhysicsComponent> _physicsComponent;

  std::shared_ptr<Vect2D> moveSpeed;
  bool canDoubleJump;
};
