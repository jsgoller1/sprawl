#include "Component.hh"

Component::Component(const shared_ptr<Identity> ownerIdentity, const bool enabled)
    : ownerIdentity(ownerIdentity), _enabled(enabled) {}

const shared_ptr<Identity> Component::getOwnerIdentity() const { return this->ownerIdentity; }
void Component::setOwnerIdentity(const shared_ptr<Identity> identity) { this->ownerIdentity = identity; }

bool Component::isEnabled() const { return this->_enabled; }
void Component::setEnabled(const bool setting) { this->_enabled = setting; }
