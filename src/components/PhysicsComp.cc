#include "PhysicsComp.hh"

PhysicsComp::PhysicsComp(const shared_ptr<PositionComp> positionComp,
                         const BoundingBoxSPtr boundingBox,
                         const bool collisionsSetting,
                         const bool gravitySetting) {
  this->positionComp = positionComp;
  this->boundingBox = boundingBox;
  this->gravityEnabled = gravitySetting;
  this->collisionsEnabled = collisionsSetting;
  this->velocity = shared_ptr<Vect2D>(new Vect2D{.x = 0, .y = 0});
}

shared_ptr<PhysicsComp> PhysicsComp::getptr() {
  return this->shared_from_this();
}

bool PhysicsComp::hasCollisions() { return this->collisionsEnabled; }
void PhysicsComp::enableCollisions(const bool setting) {
  this->collisionsEnabled = setting;
}
bool PhysicsComp::hasGravity() { return this->gravityEnabled; }
void PhysicsComp::enableGravity(const bool setting) {
  this->gravityEnabled = setting;
}

void PhysicsComp::setVelocity(const shared_ptr<Vect2D> velocity) {
  this->velocity = velocity;
}
shared_ptr<Vect2D> PhysicsComp::getVelocity() { return this->velocity; }

void PhysicsComp::addVelocity(const shared_ptr<Vect2D> velocity) {
  this->velocity->x += velocity->x;
  this->velocity->y += velocity->y;
}

shared_ptr<PhysicsMgr> PhysicsComp::getManager() { return this->manager; }
void PhysicsComp::setManager(const shared_ptr<PhysicsMgr> manager) {
  this->manager = manager;
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

bool PhysicsComp::isColliding() {
  shared_ptr<vector<shared_ptr<PhysicsComp>>> colliding =
      this->manager->getAllColliding(this->getptr());
  return !(colliding->empty());
}

shared_ptr<Vect2D> PhysicsComp::getCenter() {
  return this->positionComp->getCenter();
}

void PhysicsComp::move(shared_ptr<Vect2D> direction) {
  this->positionComp->move(direction);
}
