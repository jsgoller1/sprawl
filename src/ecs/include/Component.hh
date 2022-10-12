#pragma once

#include "Identity.hh"

class Component : public enable_shared_from_this<Component> {
 public:
  Component(const shared_ptr<Identity> ownerIdentity = nullptr);
  shared_ptr<Identity> getOwnerIdentity() const;
  void setOwnerIdentity(const shared_ptr<Identity> identity);

 private:
  shared_ptr<Identity> ownerIdentity;
};
