#include "Identity.hh"

Identity::Identity(const shared_ptr<EntityID> entityID) {
  this->entityID = entityID;
}

shared_ptr<const EntityID> Identity::getEntityID() const {
  return this->entityID;
}
