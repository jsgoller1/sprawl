#include "Component.hh"

#include "UUIDGenerator.hh"

std::string Component::toString() const { return ""; }

Component::Component(const bool enabled) : enabled(enabled) {}

std::shared_ptr<Actor> Component::getOwner() const { return this->owner; }
void Component::setOwner(const std::shared_ptr<Actor> owner) { this->owner = owner; }

bool Component::isEnabled() const { return this->enabled; }
void Component::setEnabled(const bool setting) { this->enabled = setting; }
