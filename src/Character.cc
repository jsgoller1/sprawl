#include "Character.hh"

Character::Character(const shared_ptr<GameObjectID> gameObjectID,
                     const shared_ptr<PositionComponent> positionComponent,
                     const shared_ptr<PhysicsComponent> physicsComponent,
                     const shared_ptr<DrawingComponent> drawingComponent)
    : GameObject(gameObjectID, positionComponent, physicsComponent,
                 drawingComponent) {
  this->moveSpeed = shared_ptr<Point>(new Point{.x = 10, .y = 10});
  this->jumpCount = 0;
  this->getPhysicsComponent()->enableGravity(true);
}

void Character::move(const GameAction& action) {
  // TODO: For now, no scrolling is implemented, so the
  // character cannot move past the edge of the screen.
  // Character should _not_ know about Screen.
  shared_ptr<Point> newVelocity = this->getPhysicsComponent()->getVelocity();

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
  this->getPhysicsComponent()->setVelocity(newVelocity);
}

void Character::jump() {
  // TODO: jumpCount currently does nothing useful,
  // but we will use it for double jumping eventually.
  // jumpCount++;
  LOG_INFO("Jump count: {0}", jumpCount);
  if (not(jumpCount >= 2) and
      this->getPhysicsComponent()->getVelocity()->y == 0) {
    shared_ptr<Point> newVelocity = shared_ptr<Point>(new Point{
        .x = this->getPhysicsComponent()->getVelocity()->x, .y = -20});
    this->getPhysicsComponent()->addVelocity(newVelocity);
  }
}
