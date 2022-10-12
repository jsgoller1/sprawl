#include "Component.hh"

Component::Component(const shared_ptr<Identity> ownerIdentity)
    : ownerIdentity(ownerIdentity) {}

shared_ptr<Identity> Component::getOwnerIdentity() const {
  return this->ownerIdentity;
}
void Component::setOwnerIdentity(const shared_ptr<Identity> identity) {
  this->ownerIdentity = identity;
}
