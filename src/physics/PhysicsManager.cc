#include "PhysicsManager.hh"

PhysicsManager::PhysicsManager() {
  this->managementEntries =
      shared_ptr<map<shared_ptr<Identity>, shared_ptr<ManagementEntry>>>(
          new map<shared_ptr<Identity>, shared_ptr<ManagementEntry>>());
}

PhysicsManager::ManagementEntry::ManagementEntry(
    const shared_ptr<PhysicsComponent> physicsComponent,
    const shared_ptr<PositionComponent> positionComponent,
    const shared_ptr<CollisionComponent> collisionComponent)
    : physicsComponent(physicsComponent),
      positionComponent(positionComponent),
      collisionComponent(collisionComponent) {}

std::shared_ptr<PhysicsManager> PhysicsManager::getptr() {
  // TODO: This is dangerous and leads to undefined behavior if no other
  // shared pointers to this object exist; it would be best to force
  // any construction to return a shared pointer, but that might not be
  // viable. See:
  // https://en.cppreference.com/w/cpp/memory/enable_shared_from_this
  return this->shared_from_this();
}

void PhysicsManager::manage(
    const shared_ptr<Identity> identity,
    const shared_ptr<PhysicsComponent> physicsComponent,
    const shared_ptr<PositionComponent> positionComponent,
    const shared_ptr<CollisionComponent> collisionComponent) {
  if (this->managementEntries->find(identity) !=
      this->managementEntries->end()) {
    // TODO: Log a warning
    return;
  }
  shared_ptr<ManagementEntry> entry =
      shared_ptr<ManagementEntry>(new ManagementEntry(
          physicsComponent, positionComponent, collisionComponent));
  this->managementEntries->insert(
      pair<shared_ptr<Identity>, shared_ptr<ManagementEntry>>(identity, entry));
}

void PhysicsManager::unmanage(const shared_ptr<Identity> identity) {
  if (this->managementEntries->find(identity) ==
      this->managementEntries->end()) {
    // TODO: Log a warning
    return;
  }
  this->managementEntries->erase(identity);
}

void PhysicsManager::gameLoopUpdate(const time_ms duration) {
  for (pair<shared_ptr<Identity>, shared_ptr<ManagementEntry>> mapping :
       *(this->managementEntries)) {
    shared_ptr<Identity> identity = mapping.first;
    shared_ptr<PhysicsComponent> physicsComponent =
        mapping.second->physicsComponent;
    shared_ptr<PositionComponent> positionComponent =
        mapping.second->positionComponent;
    shared_ptr<CollisionComponent> collisionComponent =
        mapping.second->collisionComponent;
    shared_ptr<set<shared_ptr<CollisionComponent>>> collisionCandidates =
        this->getCollisionCandidates(collisionComponent);

    // Apply forces, attempt movement, and determine collisions
    if (collisionComponent
            ->testCollisions(shared_ptr<Vect2D>(new Vect2D(0.0, 3.0)),
                             collisionCandidates)
            ->empty()) {
      physicsComponent->applyGravity(this->getGravityConstant());
    }
    shared_ptr<Vect2D> positionDelta = physicsComponent->integrate(duration);
    shared_ptr<CollisionTestResult> results =
        collisionComponent->testCollisions(positionDelta, collisionCandidates);
    positionComponent->setCenter(results->getValidPosition());

    // Resolve collisions
    for (shared_ptr<Collision> collision : *(results->getCollisions())) {
      shared_ptr<PhysicsComponent> target =
          this->managementEntries->find(collision->targetIdentity)
              ->second->physicsComponent;
      CollisionResolutionType type =
          physicsComponent->getCollisionResolutionType(
              target->getForceResponsive());

      physicsComponent->resolveCollision(collision, type, target);
    }
  }
}

shared_ptr<set<shared_ptr<CollisionComponent>>>
PhysicsManager::getCollisionCandidates(
    const shared_ptr<CollisionComponent> source) const {
  // TODO: Eventually, we may want to use space partitioning to limit how many
  // objects we test collisions against; for now, we just test against
  // everything
  shared_ptr<set<shared_ptr<CollisionComponent>>> collisionComponents =
      shared_ptr<set<shared_ptr<CollisionComponent>>>(
          new set<shared_ptr<CollisionComponent>>());

  shared_ptr<set<shared_ptr<Identity>>> identities =
      EntityManager::instance()->getAllIdentities();
  for (shared_ptr<Identity> identity : *identities) {
    if (this->managementEntries->find(identity) ==
        this->managementEntries->end()) {
      // TODO: Not every Entity is a GameObject (e.g. background); per note
      // above, we test against EVERYTHING.
      continue;
    }
    collisionComponents->insert(
        this->managementEntries->find(identity)->second->collisionComponent);
  }
  return collisionComponents;
}
