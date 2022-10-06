#include "EntityManager.hh"

shared_ptr<const Identity> EntityManager::createIdentity(const string& name) {}
shared_ptr<const Identity> EntityManager::createIdentity(
    const shared_ptr<string> name) {
  return this->createIdentity(*name);
}
shared_ptr<Entity> EntityManager::getEntity(
    const shared_ptr<Identity> identity) {}

// Private constructors
EntityManager::EntityManager() {
  this->entityCount = 0;
  this->entityMap =
      shared_ptr<map<shared_ptr<const Identity>, shared_ptr<Entity>>>(
          new map<shared_ptr<const Identity>, shared_ptr<Entity>>());
}
