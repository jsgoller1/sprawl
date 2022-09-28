#include "Character.hh"

Character::Character(
    const shared_ptr<Vect2D> center, const GameObjectNameSPtr name,
    const shared_ptr<CharacterPhysicsComponent> characterPhysicsComp,
    const FilePathSPtr texturePath, const DrawingCompSPtr drawingComp)
    : GameObject(center, name, texturePath, drawingComp) {
  this->canDoubleJump = true;
  this->physicsComp =
      (characterPhysicsComp == nullptr)
          ? shared_ptr<CharacterPhysicsComponent>(
                new CharacterPhysicsComponent(this->positionComp))
          : characterPhysicsComp;
  this->physicsComp->enableGravity(true);
}

void Character::move(const GameAction& action) {
  // TODO: For now, no scrolling is implemented, so the
  // character cannot move past the edge of the screen.
  // Character should _not_ know about Screen.
  switch (action) {
    case MOVE_UP:
      // TODO: Jumping / double jumping
      this->jump();
      break;
    case MOVE_LEFT:
      this->physicsComp->applyMovementForce(Direction::Left());
      break;
    case MOVE_RIGHT:
      this->physicsComp->applyMovementForce(Direction::Right());
      break;
    default:
      // TODO: should warn
      break;
  }
}
void Character::shoot(const GameAction& action) {
  this->combatCompSPtr->shoot(action);
}

void Character::jump() {
  if (not this->canDoubleJump) {
    return;
  }
  if (this->physicsComp->isMidair()) {
    this->canDoubleJump = false;
  }
  this->physicsComp->applyJumpForce();
}
