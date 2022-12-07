#pragma once

#include "RealisticPhysicsComponent.hh"

/*
CharacterPhysicsComponent is a specialized version of PhysicsComponent
that has character-related physics functionality.
*/

#define CHARACTER_ENABLE_GRAVITY true
#define CHARACTER_ENABLE_FORCE_RESPONSIVE true
#define CHARACTER_MAX_SPEED 10.0

class CharacterPhysicsComponent : public RealisticPhysicsComponent {
 public:
  CharacterPhysicsComponent(const std::shared_ptr<Identity> ownerIdentity,
                            const bool forceResponsiveSetting = CHARACTER_ENABLE_FORCE_RESPONSIVE,
                            const bool gravitySetting = CHARACTER_ENABLE_GRAVITY,
                            const DragType dragType = DragType::TIME_EXPONENTIAL, const real dragCoefficient = 0.0,
                            const PositionUnit maxSpeed = CHARACTER_MAX_SPEED, const PositionUnit minSpeed = 0.0,
                            Vect2D velocity = Vect2D::zero());
  CharacterPhysicsComponent(const std::shared_ptr<RealisticPhysicsComponent> comp);
  ~CharacterPhysicsComponent() override;

  void applyJumpForce();
  void applyMovementForce(const Direction& direction);
  bool isMidair();
};
