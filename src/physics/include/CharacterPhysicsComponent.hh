#include "PhysicsComponent.hh"

/*
CharacterPhysicsComponent is a specialized version of PhysicsComponent
that has character-related physics functionality.
*/

class CharacterPhysicsComponent : public PhysicsComponent {
 public:
  CharacterPhysicsComponent();
  void applyJumpForce();
  void applyMovementForce(const shared_ptr<Direction> direction);
};
