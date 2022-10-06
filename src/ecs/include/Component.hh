#pragma once

#include "Identity.hh"

constexpr bool COMPONENT_ENABLED = true;

class Component : public enable_shared_from_this<Component> {
 public:
  Component(shared_ptr<Identity> ownerIdentity, const bool enabled = COMPONENT_ENABLED);
  const shared_ptr<Identity> getOwnerIdentity() const;
  void setOwnerIdentity(const shared_ptr<Identity> identity);

  bool isEnabled() const;
  void setEnabled(const bool setting);

 private:
  shared_ptr<Identity> ownerIdentity;
  bool _enabled;
};
