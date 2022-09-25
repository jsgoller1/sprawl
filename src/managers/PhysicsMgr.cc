#include "PhysicsMgr.hh"

#include <algorithm>

PhysicsMgr::PhysicsMgr() {
  this->managedComponents = shared_ptr<set<shared_ptr<PhysicsComp>>>(
      new set<shared_ptr<PhysicsComp>>());
}

std::shared_ptr<PhysicsMgr> PhysicsMgr::getptr() {
  // TODO: This is dangerous and leads to undefined behavior if no other
  // shared pointers to this object exist; it would be best to force
  // any construction to return a shared pointer, but that might not be
  // viable. See:
  // https://en.cppreference.com/w/cpp/memory/enable_shared_from_this
  return this->shared_from_this();
}

void PhysicsMgr::manageComponent(const shared_ptr<PhysicsComp> component) {
  if (component->getManager() != nullptr) {
    // TODO: Log a warning
    return;
  }
  component->setManager(this->getptr());
  this->managedComponents->insert(component);
}
void PhysicsMgr::unmanageComponent(const shared_ptr<PhysicsComp> component) {
  if (component->getManager() != this->getptr()) {
    // TODO: Log a warning
    return;
  }
  component->setManager(nullptr);
  this->managedComponents->erase(component);
}

shared_ptr<vector<shared_ptr<PhysicsComp>>> PhysicsMgr::getAllColliding(
    shared_ptr<PhysicsComp> component) {
  shared_ptr<vector<shared_ptr<PhysicsComp>>> collided =
      shared_ptr<vector<shared_ptr<PhysicsComp>>>(
          new vector<shared_ptr<PhysicsComp>>());
  for (shared_ptr<PhysicsComp> other : *(this->managedComponents)) {
    if (other != component && this->areColliding(component, other)) {
      collided->push_back(other);
    }
  }
  return collided;
}

void PhysicsMgr::applyVelocity(shared_ptr<PhysicsComp> comp) {
  // Attempt to move each point according to its current velocity.
  // If it winds up colliding with something, undo the movement,
  // and set its velocity to 0.
  shared_ptr<Vect2D> velocity = comp->getVelocity();
  comp->move(velocity);
  if (comp->isColliding()) {
    // TODO: Since we don't have to do any redrawing, we can try a strategy
    // where we attempt to move half as far as we would have, then half of
    // that, etc until the movement is less than 1 pixel; this should fix the
    // "forcefield" problem.
    comp->move(
        shared_ptr<Vect2D>(new Vect2D{.x = -velocity->x, .y = -velocity->y}));
    comp->setVelocity(shared_ptr<Vect2D>(new Vect2D{.x = 0, .y = 0}));
  }
}
void PhysicsMgr::applyVelocityAll() {
  for (shared_ptr<PhysicsComp> comp : *(this->managedComponents)) {
    // TODO: applying gravity here is messy and should be done elsewhere;
    // this will just get it done for the initial MVP.
    this->applyGravity(comp);
    this->applyVelocity(comp);
  }
}
