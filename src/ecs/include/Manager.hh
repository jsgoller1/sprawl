#pragma once

#include <set>

#include "Memory.hh"

/*
 * Managers keep track of Components and facilitiate interactions between them.
 * Like real-life managers, they don't know how to do anything useful; useful
 * behavior is the responsibility of Components. The Manager is just responsible
 * for knowing which other Components a Component needs to interact with, and
 * when.
 *
 * Manager implements the Curiously Recurring Template Pattern so the same
 * management interface can be reused by derived classes (PhysicsManager,
 * AnimationManager, etc) despite them using shared pointers to different types
 * of components. Each derived class is responsible for having a
 * managedComponents attribute that supports insert() and erase() of its
 * component type.
 */
template <typename DerivedManager>
class Manager : public enable_shared_from_this<Manager<DerivedType>> {
 public:
  Manager();

  // TODO: This is dangerous and leads to undefined behavior if no other
  // shared pointers to this object exist; it would be best to force
  // any construction to return a shared pointer, but that might not be
  // viable. See:
  // https://en.cppreference.com/w/cpp/memory/enable_shared_from_this
  std::shared_ptr<Manager<DerivedType>> getptr() {
    return this->shared_from_this();
  }

  template <typename ComponentType>
  void manageComponent(const shared_ptr<ComponentType> component) {
    DerivedManager& derived = static_cast<DerivedManager&>(*this);
    if (component->getManager() != nullptr) {
      // TODO: Log a warning
      return;
    }
    component->setManager(derived->getptr());
    derived->managedComponents->insert(component);
  }

  template <typename ComponentType>
  void unmanageComponent(const shared_ptr<ComponentType> component) {
    DerivedManager& derived = static_cast<DerivedManager&>(*this);
    if (component->getManager() != derived->getptr()) {
      // TODO: Log a warning
      return;
    }
    component->setManager(nullptr);
    derived->managedComponents->erase(component);
  }

 protected:
  // TODO: I don't think we want a method for getting the managedComponents
  // set, because it would allow for it to be tampered with without the
  // components knowing.
  // TODO: We might want a `bool isManaged(component)` method.
};
