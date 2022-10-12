#include "CollisionDetectionManager.hh"

void CollisionDetectionManager::manageComponent(
    const shared_ptr<CollisionDetectionComponent> component) {
  if (component->getManager() != nullptr) {
    // TODO: Log a warning
    return;
  }
  component->setManager(this->getptr());
  this->managedComponents->insert(component);
}
void CollisionDetectionManager::unmanageComponent(
    const shared_ptr<CollisionDetectionComponent> component) {
  if (component->getManager() != this->getptr()) {
    // TODO: Log a warning
    return;
  }
  component->setManager(nullptr);
  this->managedComponents->erase(component);
}

shared_ptr<set<shared_ptr<CollisionDetectionComponent>>>
CollisionDetectionManager::getCollisionCandidates(
    const shared_ptr<CollisionDetectionComponent> source) const {
  // TODO: Eventually, we may want to use space partitioning to limit how many
  // objects we test collisions against; for now, we just test against
  // everything
  shared_ptr<set<shared_ptr<Identity>>> identities =
      EntityManager::instance()->getAllIdentities();
  shared_ptr<set<shared_ptr<CollisionDetectionComponent>>>
      collisionDetectionComponents =
          shared_ptr<set<shared_ptr<CollisionDetectionComponent>>>(
              new set<shared_ptr<CollisionDetectionComponent>>());
}
