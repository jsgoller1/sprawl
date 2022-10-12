#include "Entity.hh"

Entity::Entity(const shared_ptr<EntityName> name) {
  shared_ptr<EntityManager> entityManager = EntityManager::instance();
  this->entityName = name;
  this->identity = entityManager->manage(this, name);
}

Entity::~Entity() {
  shared_ptr<EntityManager> entityManager = EntityManager::instance();
  entityManager->unmanage(this);
}

shared_ptr<Identity> Entity::getIdentity() const { return this->identity; }

shared_ptr<EntityName> Entity::getName() const { return this->entityName; }
void Entity::setName(const shared_ptr<EntityName> entityName) {
  this->entityName = entityName;
}
