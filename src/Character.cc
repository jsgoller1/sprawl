#include "Character.hh"

#include "Logger.hh"

Character::Character(const shared_ptr<Vect2D> center,
                     const GameObjectNameSPtr name,
                     const shared_ptr<PhysicsComponent> physicsComp,
                     const FilePathSPtr texturePath,
                     const DrawingCompSPtr drawingComp)
    : GameObject(center, name, physicsComp, texturePath, drawingComp) {
  this->moveSpeed = shared_ptr<Vect2D>(new Vect2D{.x = 150, .y = 150});
  this->jumpCount = 0;
  this->physicsComp->enableGravity(true);
}

void Character::move(const GameAction& action) {
  // TODO: For now, no scrolling is implemented, so the
  // character cannot move past the edge of the screen.
  // Character should _not_ know about Screen.
  shared_ptr<Vect2D> newVelocity = this->physicsComp->getVelocity();

  switch (action) {
    case MOVE_UP:
      // TODO: Jumping / double jumping
      break;
    case MOVE_LEFT:
      newVelocity->x = -(this->moveSpeed->x);
      break;
    case MOVE_RIGHT:
      newVelocity->x = this->moveSpeed->x;
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

void Character::jump() {
  // TODO: jumpCount currently does nothing useful,
  // but we will use it for double jumping eventually.
  // jumpCount++;
  log("Jump count: " + to_string(jumpCount));
  if (not(jumpCount >= 2) and this->physicsComp->getVelocity()->y == 0) {
    shared_ptr<Vect2D> newVelocity = shared_ptr<Vect2D>(
        new Vect2D{.x = this->physicsComp->getVelocity()->x, .y = -20});
    this->physicsComp->addVelocity(newVelocity);
  }
}
