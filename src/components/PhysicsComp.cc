#include "PhysicsComp.hh"

PhysicsComp::PhysicsComp(const PositionCompSPtr positionComp,
                         const BoundingBoxSPtr boundingBox,
                         const bool collisionsSetting,
                         const bool gravitySetting) {
  this->positionComp = positionComp;
  this->boundingBox = boundingBox;
  this->gravityEnabled = gravitySetting;
  this->collisionsEnabled = collisionsSetting;
}

bool PhysicsComp::hasCollisions() { return this->collisionsEnabled; }
void PhysicsComp::setCollisions(const bool setting) {
  this->collisionsEnabled = setting;
}
bool PhysicsComp::hasGravity() { return this->gravityEnabled; }
void PhysicsComp::setGravity(const bool setting) {
  this->gravityEnabled = setting;
}

shared_ptr<PhysicsMgr> PhysicsComp::getManager() { return this->manager; }
void PhysicsComp::setManager(const shared_ptr<PhysicsMgr> manager) {
  this->manager = manager;
}
