#include "EntityManager.hh"

// Public
EntityManager::EntityManager() : entityCount(0){};

shared_ptr<Identity> EntityManager::getIdentity(
    const Entity* const entity) const {
  auto result = this->entityToIdentity->find(entity);
  if (result == this->entityToIdentity->end()) {
    return nullptr;
  }
  return result->second;
}
Entity* EntityManager::getEntity(const shared_ptr<Identity> identity) const {
  auto result = this->identityToEntity->find(identity);
  if (result == this->identityToEntity->end()) {
    return nullptr;
  }
  return (Entity*)(result->second);
}

// Private
shared_ptr<Identity> EntityManager::manage(const Entity* const entity) {
  if (this->entityToIdentity->find(entity) != this->entityToIdentity->end()) {
    // TODO: Log warning here
    return nullptr;
  }

  shared_ptr<Identity> identity = this->createIdentity();

  this->identityToEntity->insert(
      pair<shared_ptr<Identity>, const Entity* const>(identity, entity));
  this->entityToIdentity->insert(
      pair<const Entity* const, shared_ptr<Identity>>(entity, identity));

  return identity;
}
void EntityManager::unmanage(const Entity* const entity) {
  if (this->entityToIdentity->find(entity) == this->entityToIdentity->end()) {
    // TODO: Log warning here
    return;
  }

  shared_ptr<Identity> identity = this->getIdentity(entity);
  identityToEntity->erase(identity);
  entityToIdentity->erase(entity);
}

shared_ptr<Identity> EntityManager::createIdentity() {
  this->entityCount++;
  shared_ptr<EntityID> entityID = shared_ptr<EntityID>(
      new EntityID("entity-" + to_string(this->entityCount)));
  shared_ptr<Identity> identity = shared_ptr<Identity>(new Identity(entityID));
}
