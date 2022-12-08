#include "Identity.hh"

#include "fmt/format.h"

Identity::Identity(const EntityID& entityID) : _entityID(EntityID(entityID)) {}

const EntityID& Identity::getEntityID() const { return this->_entityID; }

std::string Identity::toString() { return fmt::format("Identity(entityID: {0})", this->_entityID); }
