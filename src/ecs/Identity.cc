#include "Identity.hh"

#include "format.h"

Identity::Identity(const shared_ptr<EntityID> entityID) { this->entityID = entityID; }

shared_ptr<const EntityID> Identity::getEntityID() const { return this->entityID; }

string Identity::toString() { return fmt::format("Identity(entityID: {0})", *this->entityID); }
