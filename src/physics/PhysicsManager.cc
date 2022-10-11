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

shared_ptr<set<shared_ptr<PhysicsComponent>>>
PhysicsManager::getCollisionCandidates(shared_ptr<PhysicsComponent> component) {
  // TODO: Eventually, we won't want to test against all managed components
  // when doing collisions (i.e. we'll probably do screen partitioning in Zone,
  // and then PhysicsManager will ask Zone for a list of GameObjects in the same
  // partition)
  return this->managedComponents;
}

void PhysicsManager::updateManagedComponents(const time_ms duration) {
  for (shared_ptr<PhysicsComponent> comp : *(this->managedComponents)) {
    comp->applyGravity();
    comp->integrate(duration);
  }
}

shared_ptr<PhysicsComponent> PhysicsManager::getComponent(
    const shared_ptr<Identity> identity) {
  shared_ptr<EntityManager> entityManager = EntityManager::instance();
  Entity* entity = entityManager->getEntity(identity);
  if (entity == nullptr) {
    // TODO: Log warning
    return nullptr;
  }
  shared_ptr<PhysicsComponent> comp =
      static_cast<GameObject*>(entity)->getPhysicsComponent();
  if (this->managedComponents->find(comp) == this->managedComponents->end()) {
    // TODO: Log warning
    return nullptr;
  }
  return comp;
}
