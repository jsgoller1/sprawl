#pragma once

#include <memory>

#include "Identity.hh"

constexpr bool COMPONENT_ENABLED = true;

class Component : public std::enable_shared_from_this<Component> {
 public:
  Component(const std::shared_ptr<Identity> ownerIdentity = nullptr, const bool enabled = COMPONENT_ENABLED);
  const std::shared_ptr<Identity> getOwnerIdentity() const;
  void setOwnerIdentity(const std::shared_ptr<Identity> identity);

  bool isEnabled() const;
  void setEnabled(const bool setting);

 private:
  std::shared_ptr<Identity> ownerIdentity;
  bool _enabled;
};

template <typename T>
std::shared_ptr<T> getSharedPointer(T& component) {
  // TODO: This leads to undefined behavior if no other shared pointers to this object exist.
  // https://en.cppreference.com/w/cpp/memory/enable_shared_from_this
  return static_pointer_cast<T, Component>(component.shared_from_this());
}
