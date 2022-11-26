#include "Identity.hh"

#include "fmt/format.h"

Identity::Identity(const std::shared_ptr<EntityID> entityID) { this->entityID = entityID; }

std::shared_ptr<const EntityID> Identity::getEntityID() const { return this->entityID; }

std::string Identity::toString() { return fmt::format("Identity(entityID: {0})", *this->entityID); }
