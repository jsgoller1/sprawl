#pragma once

#include "Identity.hh"

class Component : public enable_shared_from_this<Component> {
 public:
  shared_ptr<Identity> getOwnerIdentity() const;

 private:
  shared_ptr<Identity> ownerIdentity;
};
