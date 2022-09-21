#include "Character.hh"

Character::Character(const PointSPtr center, const GameObjectNameSPtr name,
                     const shared_ptr<PhysicsComp> physicsComp,
                     const FilePathSPtr texturePath,
                     const DrawingCompSPtr drawingComp)
    : GameObject(center, name, physicsComp, texturePath, drawingComp) {
  this->moveSpeed = PointSPtr(new Point{.x = 10, .y = 10});
}

void Character::move(const GameAction& action) {
  // TODO: For now, no scrolling is implemented, so the
  // character cannot move past the edge of the screen.
  // Character should _not_ know about Screen.
  PointSPtr newVelocity = this->physicsComp->getVelocity();

  switch (action) {
    case MOVE_UP:
      // TODO: Jumping / double jumping
      break;
    case MOVE_LEFT:
      newVelocity->x = this->moveSpeed->x;
      break;
    case MOVE_RIGHT:
      newVelocity->x = -(this->moveSpeed->x);
      break;
    case STOP_MOVE_RIGHT:
    case STOP_MOVE_LEFT:
      newVelocity->x = 0;
      break;
    default:
      // TODO: should warn
      break;
  }
  this->physicsComp->setVelocity(newVelocity);
}
void Character::shoot(const GameAction& action) {
  this->combatCompSPtr->shoot(action);
}
