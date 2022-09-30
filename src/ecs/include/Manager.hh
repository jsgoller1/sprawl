#pragma once

#include <set>

#include "Component.hh"
#include "Memory.hh"

/*
 * Managers keep track of Components and facilitiate interactions between them.
 * Like real-life managers, they don't know how to do anything useful; useful
 * behavior is the responsibility of Components. The Manager is just responsible
 * for knowing which other Components a Component needs to interact with, and
 * when.
 */

class Manager : public enable_shared_from_this<Manager> {
 public:
  Manager();
  std::shared_ptr<Manager> getptr();
  void manageComponent(const shared_ptr<Component> component);
  void unmanageComponent(const shared_ptr<Component> component);

 private:
  // TODO: I don't think we want a method for getting the managedComponents
  // set, because it would allow for it to be tampered with without the
  // components knowing.
  // TODO: We might want a `bool isManaged(component)` method.
  shared_ptr<std::set<shared_ptr<Component>>> managedComponents;
};
