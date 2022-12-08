#include "Entity.hh"

#include "EntityManager.hh"

Entity::Entity(const EntityName name) {
  std::shared_ptr<EntityManager> entityManager = EntityManager::instance();
  this->_name = name;
  this->_identity = entityManager->manage(this, name);
}

Entity::~Entity() {
  std::shared_ptr<EntityManager> entityManager = EntityManager::instance();
  entityManager->unmanage(this);
}

Identity& Entity::getIdentity() const { return *(this->_identity); }

EntityName Entity::getName() const { return this->_name; }
void Entity::setName(const EntityName name) { this->_name = name; }
