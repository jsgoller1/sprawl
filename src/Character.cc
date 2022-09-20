#include "Character.hh"

Character::Character(const PointSPtr center, const GameObjectNameSPtr name,
                     const PhysicsCompSPtr physicsComp,
                     const FilePathSPtr texturePath,
                     const DrawingCompSPtr drawingComp)
    : GameObject(center, name, physicsComp, texturePath, drawingComp) {}

void Character::move(const GameAction& action) {
  // TODO: For now, no scrolling is implemented, so the
  // character cannot move past the edge of the screen.
  // Character should _not_ know about Screen.
  switch (action) {
    case MOVE_UP:
      this->positionComp->updateY(-100);
      break;
    case MOVE_DOWN:
      this->positionComp->updateY(100);
      break;
    case MOVE_LEFT:
      this->positionComp->updateX(-100);
      break;
    case MOVE_RIGHT:
      this->positionComp->updateX(100);
      break;
  }
}
void Character::shoot(const GameAction& action) {
  this->combatCompSPtr->shoot(action);
}
