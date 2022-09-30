#include "Manager.hh"

// TODO: This is dangerous and leads to undefined behavior if no other
// shared pointers to this object exist; it would be best to force
// any construction to return a shared pointer, but that might not be
// viable. See:
// https://en.cppreference.com/w/cpp/memory/enable_shared_from_this
std::shared_ptr<Manager> Manager::getptr() { return this->shared_from_this(); }

void Manager::manageComponent(const shared_ptr<Component> component) {
  if (component->getManager() != nullptr) {
    // TODO: Log a warning
    return;
  }
  component->setManager(this->getptr());
  this->managedComponents->insert(component);
}
void Manager::unmanageComponent(const shared_ptr<Component> component) {
  if (component->getManager() != this->getptr()) {
    // TODO: Log a warning
    return;
  }
  component->setManager(nullptr);
  this->managedComponents->erase(component);
}
