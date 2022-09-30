#include "PhysicsComp.hh"

PhysicsComp::PhysicsComp(const shared_ptr<const Identity> parentIdentity,
                         const PositionCompSPtr positionComp,
                         const BoundingBoxSPtr boundingBox,
                         const bool collisionsSetting,
                         const bool gravitySetting)
    : Component(parentIdentity) {
  this->positionComp = positionComp;
  this->boundingBox = boundingBox;
  this->gravityEnabled = gravitySetting;
  this->collisionsEnabled = collisionsSetting;
  this->velocity = PointSPtr(new Point{.x = 0, .y = 0});
}

bool PhysicsComp::hasCollisions() { return this->collisionsEnabled; }
void PhysicsComp::enableCollisions(const bool setting) {
  this->collisionsEnabled = setting;
}
bool PhysicsComp::hasGravity() { return this->gravityEnabled; }
void PhysicsComp::enableGravity(const bool setting) {
  this->gravityEnabled = setting;
}

void PhysicsComp::setVelocity(const PointSPtr velocity) {
  this->velocity = velocity;
}
PointSPtr PhysicsComp::getVelocity() { return this->velocity; }

void PhysicsComp::addVelocity(const PointSPtr velocity) {
  this->velocity->x += velocity->x;
  this->velocity->y += velocity->y;
}

void PhysicsComp::setBoundingBox(const BoundingBoxSPtr box) {
  this->boundingBox = box;
}

void PhysicsComp::setBoundingBox(const PositionUnit height,
                                 const PositionUnit width) {
  this->boundingBox = shared_ptr<BoundingBox>(
      new BoundingBox{.height = height, .width = width});
}

shared_ptr<BoundingBox> PhysicsComp::getBoundingBox() {
  return this->boundingBox;
}

PointSPtr PhysicsComp::getCenter() { return this->positionComp->getCenter(); }

void PhysicsComp::move(PointSPtr direction) {
  this->positionComp->move(direction);
}
