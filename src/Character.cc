#include "Character.hh"

Character::Character(
    const shared_ptr<Vect2D> center, const GameObjectNameSPtr name,
    const shared_ptr<CharacterPhysicsComponent> characterPhysicsComp,
    const FilePathSPtr texturePath, const DrawingCompSPtr drawingComp)
    : GameObject(center, name, texturePath, drawingComp) {
  this->canDoubleJump = true;
  this->setPhysicsComponent(
      (characterPhysicsComp == nullptr)
          ? shared_ptr<CharacterPhysicsComponent>(new CharacterPhysicsComponent(
                this->getName(), this->getPositionComponent()))
          : characterPhysicsComp);
  this->getPhysicsComponent()->enableGravity(true);
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
      this->getPhysicsComponent()->applyMovementForce(Direction::Left());
      break;
    case MOVE_RIGHT:
      this->getPhysicsComponent()->applyMovementForce(Direction::Right());
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
  if (this->getPhysicsComponent()->isMidair()) {
    this->canDoubleJump = false;
  }
  this->getPhysicsComponent()->applyJumpForce();
}
