#include "Entity.hh"

Entity::Entity(const EntityName name) {
  shared_ptr<EntityManager> entityManager = EntityManager::instance();
  this->_name = name;
  this->_identity = entityManager->manage(this, name);
}

Entity::~Entity() {
  shared_ptr<EntityManager> entityManager = EntityManager::instance();
  entityManager->unmanage(this);
}

shared_ptr<Identity> Entity::getIdentity() const { return this->_identity; }

EntityName Entity::getName() const { return this->_name; }
void Entity::setName(const EntityName name) { this->_name = name; }
