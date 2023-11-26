#include "Component.hh"

#include "UUIDGenerator.hh"

std::string Component::toString() const { return ""; }

Component::Component(const std::weak_ptr<Actor> owner, const bool enabled) : owner(owner), enabled(enabled) {}

std::shared_ptr<Actor> Component::getOwner() const { return this->owner; }

bool Component::isEnabled() const { return this->enabled; }
void Component::setEnabled(const bool setting) { this->enabled = setting; }
