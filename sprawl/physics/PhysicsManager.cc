#include "PhysicsManager.hh"

#include "Assumption.hh"

PhysicsManager::PhysicsManager() {
  this->managementEntries = std::shared_ptr<std::map<std::shared_ptr<Identity>, std::shared_ptr<ManagementEntry>>>(
      new std::map<std::shared_ptr<Identity>, std::shared_ptr<ManagementEntry>>());
}

PhysicsManager::ManagementEntry::ManagementEntry(const std::shared_ptr<PhysicsComponent> physicsComponent,
                                                 const std::shared_ptr<PositionComponent> positionComponent,
                                                 const std::shared_ptr<CollisionComponent> collisionComponent)
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

void PhysicsManager::manage(const std::shared_ptr<Identity> identity,
                            const std::shared_ptr<PhysicsComponent> physicsComponent,
                            const std::shared_ptr<PositionComponent> positionComponent,
                            const std::shared_ptr<CollisionComponent> collisionComponent) {
  if (this->managementEntries->find(identity) != this->managementEntries->end()) {
    // TODO: Log a warning
    return;
  }
  std::shared_ptr<ManagementEntry> entry =
      std::shared_ptr<ManagementEntry>(new ManagementEntry(physicsComponent, positionComponent, collisionComponent));
  this->managementEntries->insert(
      std::pair<std::shared_ptr<Identity>, std::shared_ptr<ManagementEntry>>(identity, entry));
}

void PhysicsManager::unmanage(const std::shared_ptr<Identity> identity) {
  if (this->managementEntries->find(identity) == this->managementEntries->end()) {
    // TODO: Log a warning
    return;
  }
  this->managementEntries->erase(identity);
}

std::shared_ptr<PhysicsComponent> PhysicsManager::getManagedPhysicsComponent(
    const std::shared_ptr<Identity> identity) const {
  auto it = this->managementEntries->find(identity);
  return (it == this->managementEntries->end() ? nullptr : it->second->physicsComponent);
}

real PhysicsManager::getGravityConstant() const { return this->gravityConstant; }
void PhysicsManager::setGravityConstant(const real gravityConstant) { this->gravityConstant = gravityConstant; }

void PhysicsManager::gameLoopUpdate(const time_ms duration) {
  for (std::pair<std::shared_ptr<Identity>, std::shared_ptr<ManagementEntry>> mapping : *(this->managementEntries)) {
    std::shared_ptr<Identity> identity = mapping.first;
    std::shared_ptr<PhysicsComponent> physicsComponent = mapping.second->physicsComponent;
    std::shared_ptr<PositionComponent> positionComponent = mapping.second->positionComponent;
    std::shared_ptr<CollisionComponent> collisionComponent = mapping.second->collisionComponent;
    std::shared_ptr<std::set<std::shared_ptr<CollisionComponent>>> collisionCandidates =
        this->getCollisionCandidates(collisionComponent);
    LOG_DEBUG_SYS(PHYSICS, "Physics update beginning: {}", *physicsComponent->getOwnerIdentity()->getEntityID());
    LOG_DEBUG_SYS(PHYSICS, "Position: {}", positionComponent->getCenter().to_string());

    Vect2D positionDelta = physicsComponent->integrate(duration);
    if (positionDelta == Vect2D::zero()) {
      LOG_DEBUG_SYS(PHYSICS, "No movement, collisions skipped: {}",
                    physicsComponent->getOwnerIdentity()->getEntityID()->c_str());
      continue;
    }
    LOG_DEBUG_SYS(PHYSICS, "{} attempting movement {}", physicsComponent->getOwnerIdentity()->getEntityID()->c_str(),
                  positionDelta.to_string());

    // Test for collisions, and determine what our final position should be.
    std::shared_ptr<std::vector<Collision>> collisions =
        collisionComponent->predictMovementCollisions(positionDelta, collisionCandidates);
    Vect2D finalPosition =
        (collisions->empty()) ? positionComponent->getCenter() + positionDelta : (*collisions->begin()).finalPosition();
    positionComponent->setCenter(finalPosition);

#ifdef DIAGNOSTIC_COLLISIONS_NO_OVERLAPS
    ASSUMPTION(this->diagnosticNoOverlaps(), "No objects on screen are overlapping.")
#endif

    for (Collision collision : *collisions) {
      physicsComponent->resolveCollision(collision);
    }
    LOG_DEBUG_SYS(PHYSICS, "Physics update completed: {}", physicsComponent->getOwnerIdentity()->getEntityID());
  }
}

std::shared_ptr<std::set<std::shared_ptr<CollisionComponent>>> PhysicsManager::getCollisionCandidates(
    const std::shared_ptr<CollisionComponent> source) const {
  // TODO: Eventually, we may want to use space partitioning to limit how many
  // objects we test collisions against; for now, we just test against
  // everything
  (void)source;

  std::shared_ptr<std::set<std::shared_ptr<CollisionComponent>>> collisionComponents =
      std::shared_ptr<std::set<std::shared_ptr<CollisionComponent>>>(
          new std::set<std::shared_ptr<CollisionComponent>>());

  std::shared_ptr<std::set<std::shared_ptr<Identity>>> identities = EntityManager::instance()->getAllIdentities();
  for (std::shared_ptr<Identity> identity : *identities) {
    auto entry = this->managementEntries->find(identity);
    if (entry == this->managementEntries->end() || entry->first == source->getOwnerIdentity()) {
      // We only want collision components for physics objects we're managing, excluding
      // ourselves (because we are never colliding with ourself).
      continue;
    }
    collisionComponents->insert(this->managementEntries->find(identity)->second->collisionComponent);
  }

  return collisionComponents;
}

/*
 * FOR DEBUGGING ONLY. Tests whether any items currently managed by the physics manager are actually overlapping, and
 * thus would trigger a collision without moving. This should _never_ occur, so this function should in theory always
 * return true. This function is O(n^2) (very slow); this will crush framerate!
 */
bool PhysicsManager::diagnosticNoOverlaps() const {
  std::vector<std::shared_ptr<CollisionComponent>> components = std::vector<std::shared_ptr<CollisionComponent>>();
  for (auto comp : *this->managementEntries) {
    components.push_back(comp.second->collisionComponent);
  }

  for (unsigned long i = 0; i < components.size(); i++) {
    CollisionComponent source = *components[i];
    for (unsigned long j = i + 1; j < components.size(); j++) {
      CollisionComponent target = *components[j];
      if (source.isColliding(target, Vect2D::zero())) {
        LOG_ERROR_SYS(COLLISIONS, "{} is overlapping with {}!", *source.getOwnerIdentity()->getEntityID(),
                      *target.getOwnerIdentity()->getEntityID());
        return false;
      }
    }
  }
  return true;
}
