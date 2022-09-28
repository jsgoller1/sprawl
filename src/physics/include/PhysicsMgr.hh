#pragma once

#include <set>

#include "Memory.hh"
#include "PhysicsComp.hh"
#include "Time.hh"

/*
The PhysicsManager class handles interactions between PhysicsComp objects. Like
a real-life manager, it doesn't know how to do anything useful - it can only
tell things it manages how to interact with each other, and it handles their
interactions with the outside world so they don't have to. It relies on
PhysicsComp to know how to do useful stuff, and just needs to tell it when.

PhysicsManager knows about GameObjects, and how to determine which PhysicsComp
is owned by which GameObject.

*/

// Forward decls
class PhysicsComp;  // see PhysicsComp.hh

class PhysicsMgr : public enable_shared_from_this<PhysicsMgr> {
 public:
  PhysicsMgr();
  std::shared_ptr<PhysicsMgr> getptr();

 public:
  void updateManagedComponents(const time_ms duration);
  shared_ptr<vector<shared_ptr<PhysicsComp>>> getAllColliding(
      shared_ptr<PhysicsComp> component);
  void manageComponent(const shared_ptr<PhysicsComp> component);
  void unmanageComponent(const shared_ptr<PhysicsComp> component);

 private:
  shared_ptr<std::set<shared_ptr<PhysicsComp>>> managedComponents;
};
