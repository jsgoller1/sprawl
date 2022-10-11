
#pragma once

#include "CharacterPhysicsComponent.hh"
#include "GameAction.hh"
#include "GameObject.hh"
#include "Logger.hh"
#include "Memory.hh"
#include "PhysicsComponent.hh"
#include "PositionComponent.hh"
#include "Types.hh"

class Character : public GameObject {
  /*
   * Characters are actual characters in the game, both the player character
   * (PC) and non-player characters (NPCs)
   */
 public:
  Character(const shared_ptr<EntityName> name = nullptr,
            const shared_ptr<PositionComponent> positionComponent = nullptr,
            const shared_ptr<CollisionDetectionComponent>
                collisionDetectionComponent = nullptr,
            const shared_ptr<PhysicsComponent> physicsComponent = nullptr,
            const shared_ptr<DrawingComponent> drawingComponent = nullptr);
  void move(const GameAction& action);
  void jump();

  shared_ptr<CharacterPhysicsComponent> getPhysicsComponent() const;
  void setPhysicsComponent(
      const shared_ptr<CharacterPhysicsComponent> physicsComponent) const;

 private:
  shared_ptr<CharacterPhysicsComponent> physicsComponent;

  shared_ptr<Vect2D> moveSpeed;
  bool canDoubleJump;

  virtual void setPhysicsComponent_impl(PhysicsComponent* const comp) override;
  virtual CharacterPhysicsComponent* getPhysicsComponent_impl() const override;
};
