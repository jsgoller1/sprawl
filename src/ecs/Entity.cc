#include "Entity.hh"

Entity::Entity() {
  shared_ptr<EntityManager> entityManager = EntityManager::instance();
  this->identity = entityManager->manage(this);
}
Entity::~Entity() {
  shared_ptr<EntityManager> entityManager = EntityManager::instance();
  entityManager->unmanage(this);
}

shared_ptr<Identity> Entity::getIdentity() const { return this->identity; }
