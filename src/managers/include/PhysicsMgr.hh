#pragma once

#include <set>

#include "Manager.hh"
#include "Memory.hh"

using std::set;

// Forward decls
class PhysicsComp;  // see PhysicsComp.hh

class PhysicsMgr : public Manager {
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
  void applyGravity(shared_ptr<PhysicsComp> comp);
  void applyVelocity(shared_ptr<PhysicsComp> comp);
  void applyVelocityAll();
};

bool areLinesIntersecting(const PositionUnit low1, const PositionUnit hi1,
                          const PositionUnit low2, const PositionUnit hi2);
