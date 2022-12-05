
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

  std::shared_ptr<CharacterPhysicsComponent> getPhysicsComponent() const;
  void setPhysicsComponent(const std::shared_ptr<CharacterPhysicsComponent> characterPhysicsComponent);

 private:
  std::shared_ptr<CharacterPhysicsComponent> characterPhysicsComponent;

  std::shared_ptr<Vect2D> moveSpeed;
  bool canDoubleJump;

  virtual CharacterPhysicsComponent* getPhysicsComponent_impl() const override;
};
