#include "Entity.hh"

#include "UUIDGenerator.hh"

Entity::Entity() { this->uuid = UUIDGenerator::instance().generate(); }

Entity::~Entity() = default;

UUID Entity::getUUID() const { return this->uuid; }
