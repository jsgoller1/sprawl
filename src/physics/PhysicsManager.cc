#include "PhysicsManager.hh"

PhysicsManager::PhysicsManager() {
  this->managedComponents = shared_ptr<std::set<shared_ptr<PhysicsComponent>>>(
      new std::set<shared_ptr<PhysicsComponent>>());
}

std::shared_ptr<PhysicsManager> PhysicsManager::getptr() {
  // TODO: This is dangerous and leads to undefined behavior if no other
  // shared pointers to this object exist; it would be best to force
  // any construction to return a shared pointer, but that might not be
  // viable. See:
  // https://en.cppreference.com/w/cpp/memory/enable_shared_from_this
  return this->shared_from_this();
}

void PhysicsManager::manageComponent(
    const shared_ptr<PhysicsComponent> component) {
  if (component->getManager() != nullptr) {
    // TODO: Log a warning
    return;
  }
  component->setManager(this->getptr());
  this->managedComponents->insert(component);
}
void PhysicsManager::unmanageComponent(
    const shared_ptr<PhysicsComponent> component) {
  if (component->getManager() != this->getptr()) {
    // TODO: Log a warning
    return;
  }
  component->setManager(nullptr);
  this->managedComponents->erase(component);
}

shared_ptr<vector<shared_ptr<PhysicsComponent>>>
PhysicsManager::getAllColliding(shared_ptr<PhysicsComponent> component) {
  shared_ptr<vector<shared_ptr<PhysicsComponent>>> collided =
      shared_ptr<vector<shared_ptr<PhysicsComponent>>>(
          new vector<shared_ptr<PhysicsComponent>>());
  for (shared_ptr<PhysicsComponent> other : *(this->managedComponents)) {
    if (other != component && component->checkCollision(other)) {
      collided->push_back(other);
    }
  }
  return collided;
}

void PhysicsManager::updateManagedComponents(const time_ms duration) {
  for (shared_ptr<PhysicsComponent> comp : *(this->managedComponents)) {
    // TODO: applying gravity here is messy and should be done elsewhere;
    // this will just get it done for the initial MVP.
    comp->integrate(duration);
  }
}
