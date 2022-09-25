#include "PhysicsComp.hh"

PhysicsComp::PhysicsComp(const shared_ptr<PositionComp> positionComp,
                         const shared_ptr<BoundingBox> boundingBox,
                         const bool collisionsSetting,
                         const bool gravitySetting) {
  this->positionComp = positionComp;
  this->boundingBox = boundingBox;
  this->gravityEnabled = gravitySetting;
  this->collisionsEnabled = collisionsSetting;
  this->velocity = shared_ptr<Vect2D>(new Vect2D(0, 0));
}

shared_ptr<PhysicsComp> PhysicsComp::getptr() {
  return this->shared_from_this();
}

bool PhysicsComp::hasCollisions() const { return this->collisionsEnabled; }
void PhysicsComp::enableCollisions(const bool setting) {
  this->collisionsEnabled = setting;
}
bool PhysicsComp::hasGravity() const { return this->gravityEnabled; }
void PhysicsComp::enableGravity(const bool setting) {
  this->gravityEnabled = setting;
}

shared_ptr<Vect2D> PhysicsComp::getVelocity() const { return this->velocity; }

shared_ptr<PhysicsMgr> PhysicsComp::getManager() { return this->manager; }
void PhysicsComp::setManager(const shared_ptr<PhysicsMgr> manager) {
  this->manager = manager;
}

void PhysicsComp::setBoundingBox(const shared_ptr<BoundingBox> box) {
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

bool PhysicsComp::isColliding(const shared_ptr<PhysicsComp> comp) const {
  shared_ptr<BoundingBox> usBox =
      shared_ptr<BoundingBox>(new BoundingBox(this->boundingBoxParams));
  shared_ptr<BoundingBox> themBox =
      shared_ptr<BoundingBox>(new BoundingBox(comp->boundingBoxParams));
  return usBox->isColliding(themBox);
}
