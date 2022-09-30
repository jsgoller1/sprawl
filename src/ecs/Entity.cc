#include "Entity.hh"

Entity::Entity(const std::string& name) {
  this->identity = IdentityManager::instance()->getNewIdentity(name);
}
