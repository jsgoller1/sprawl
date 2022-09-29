#pragma once

#include "PhysicsComponent.hh"

/*
CharacterPhysicsComponent is a specialized version of PhysicsComponent
that has character-related physics functionality.
*/

class CharacterPhysicsComponent : public PhysicsComponent {
 public:
  CharacterPhysicsComponent(
      const shared_ptr<PositionComp> positionComp,
      const shared_ptr<BoundingBoxParams> boundingBoxParams = nullptr,
      const bool collisionsSetting = false, const bool gravitySetting = false);
  void applyJumpForce();
  void applyMovementForce(const shared_ptr<Direction> direction);

 private:
  PositionUnit jumpSpeed;
  PositionUnit moveSpeed;
};
