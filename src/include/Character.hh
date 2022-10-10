
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
  // Self explanatory: parent class for player, npcs, enemies, etc
 public:
  Character(const shared_ptr<Identity> identity,
            const shared_ptr<PositionComponent> positionComponent,
            const shared_ptr<PhysicsComponent> physicsComponent = nullptr,
            const shared_ptr<CollisionDetectionComponent>
                collisionDetectionComponent = nullptr,
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
