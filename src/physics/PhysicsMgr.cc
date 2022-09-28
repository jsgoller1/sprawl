#include "PhysicsMgr.hh"

#include <algorithm>

PhysicsMgr::PhysicsMgr() {
  this->managedComponents = shared_ptr<std::set<shared_ptr<PhysicsComp>>>(
      new std::set<shared_ptr<PhysicsComp>>());
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
    if (other != component && component->isColliding(other)) {
      collided->push_back(other);
    }
  }
  return collided;
}

void PhysicsMgr::updateManagedComponents(const time_ms duration) {
  for (shared_ptr<PhysicsComp> comp : *(this->managedComponents)) {
    // TODO: applying gravity here is messy and should be done elsewhere;
    // this will just get it done for the initial MVP.
    comp->integrate(duration);
  }
}
