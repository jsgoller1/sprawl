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
  bool areColliding(const shared_ptr<PhysicsComp> comp1,
                    const shared_ptr<PhysicsComp> comp2);
  shared_ptr<vector<shared_ptr<PhysicsComp>>> getAllColliding(
      shared_ptr<PhysicsComp> component);
  void applyGravity();
  void manageComponent(const shared_ptr<PhysicsComp> component);
  void unmanageComponent(const shared_ptr<PhysicsComp> component);

 private:
  shared_ptr<set<shared_ptr<PhysicsComp>>> managedComponents;
};

bool areLinesIntersecting(const PositionUnit low1, const PositionUnit hi1,
                          const PositionUnit low2, const PositionUnit hi2);
