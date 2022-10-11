#include "Component.hh"

shared_ptr<Identity> Component::getOwnerIdentity() const {
  return this->ownerIdentity;
}
