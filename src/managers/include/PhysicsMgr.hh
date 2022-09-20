#pragma once

#include <set>

#include "Memory.hh"
#include "PhysicsComp.hh"

using std::set;

// Forward decls
class PhysicsComp;  // see PhysicsComp.hh

class PhysicsMgr : public enable_shared_from_this<PhysicsMgr> {
  // Keeps track of registered PhyiscsComponents and knows how to apply physics
  // to them

 public:
  PhysicsMgr();

  std::shared_ptr<PhysicsMgr> getptr();

 public:
  void applyGravity();
  void manageComponent(const shared_ptr<PhysicsComp> component);
  void unmanageComponent(const shared_ptr<PhysicsComp> component);

 private:
  shared_ptr<set<shared_ptr<PhysicsComp>>> managedComponents;
};

// typedef shared_ptr<PhysicsMgr> PhysicsMgrSPtr;
