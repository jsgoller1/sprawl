#pragma once

#include <memory>

#include "Identity.hh"

constexpr bool COMPONENT_ENABLED = true;

class Component : public std::enable_shared_from_this<Component> {
 public:
  Component(std::shared_ptr<Identity> ownerIdentity = nullptr, const bool enabled = COMPONENT_ENABLED);
  const std::shared_ptr<Identity> getOwnerIdentity() const;
  void setOwnerIdentity(const std::shared_ptr<Identity> identity);

  bool isEnabled() const;
  void setEnabled(const bool setting);

 private:
  std::shared_ptr<Identity> ownerIdentity;
  bool _enabled;
};
