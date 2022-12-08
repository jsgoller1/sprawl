#include "EntityManager.hh"

#include "Entity.hh"
#include "fmt/format.h"

// Public
EntityManager::EntityManager() : entityCount(0) {
  this->identityToEntity =
      std::shared_ptr<std::map<std::shared_ptr<Identity>, Entity*>>(new std::map<std::shared_ptr<Identity>, Entity*>());
  this->entityToIdentity =
      std::shared_ptr<std::map<Entity*, std::shared_ptr<Identity>>>(new std::map<Entity*, std::shared_ptr<Identity>>());
};

std::shared_ptr<Identity> EntityManager::getIdentity(Entity* entity) const {
  auto result = this->entityToIdentity->find(entity);
  if (result == this->entityToIdentity->end()) {
    return nullptr;
  }
  return result->second;
}
Entity* EntityManager::getEntity(const std::shared_ptr<Identity> identity) const {
  auto result = this->identityToEntity->find(identity);
  if (result == this->identityToEntity->end()) {
    return nullptr;
  }
  return result->second;
}

// Private
std::shared_ptr<Identity> EntityManager::manage(Entity* entity, const EntityName& name) {
  if (this->entityToIdentity->find(entity) != this->entityToIdentity->end()) {
    // TODO: Log warning here
    return nullptr;
  }
  std::shared_ptr<Identity> identity = this->createIdentity(name);
  this->identityToEntity->insert(std::pair<std::shared_ptr<Identity>, Entity*>(identity, entity));
  this->entityToIdentity->insert(std::pair<Entity*, std::shared_ptr<Identity>>(entity, identity));
  return identity;
}
void EntityManager::unmanage(Entity* entity) {
  if (this->entityToIdentity->find(entity) == this->entityToIdentity->end()) {
    // TODO: Log warning here
    return;
  }

  std::shared_ptr<Identity> identity = this->getIdentity(entity);
  identityToEntity->erase(identity);
  entityToIdentity->erase(entity);
}

std::shared_ptr<Identity> EntityManager::createIdentity(const EntityName name) {
  this->entityCount++;
  EntityName actualName = fmt::format("{0}-{1}", (name.size() ? name : "Entity-"), std::to_string(this->entityCount));
  return std::shared_ptr<Identity>(new Identity(actualName));
}

std::shared_ptr<std::set<Entity*>> EntityManager::getAllEntities() {
  std::shared_ptr<std::set<Entity*>> entities = std::shared_ptr<std::set<Entity*>>(new std::set<Entity*>());
  for (auto entry : *(this->entityToIdentity)) {
    entities->insert(entry.first);
  }
  return entities;
}

std::shared_ptr<std::set<std::shared_ptr<Identity>>> EntityManager::getAllIdentities() {
  std::shared_ptr<std::set<std::shared_ptr<Identity>>> identities =
      std::shared_ptr<std::set<std::shared_ptr<Identity>>>(new std::set<std::shared_ptr<Identity>>());
  for (auto entry : *(this->identityToEntity)) {
    identities->insert(entry.first);
  }
  return identities;
}
