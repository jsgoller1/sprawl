#pragma once
#include <algorithm>
#include <set>
#include <vector>

#include "Manager.hh"
#include "Memory.hh"
#include "PhysicsComp.hh"
#include "PositionComp.hh"

class PhysicsMgr : public Manager<PhysicsMgr> {
 public:
  bool isColliding(const shared_ptr<PhysicsComp> comp1);
  bool isColliding(const shared_ptr<PhysicsComp> comp1,
                   const shared_ptr<PhysicsComp> comp2);
  shared_ptr<std::vector<shared_ptr<PhysicsComp>>> getAllColliding(
      shared_ptr<PhysicsComp> component);
  void applyGravity(shared_ptr<PhysicsComp> comp);
  void applyVelocity(shared_ptr<PhysicsComp> comp);
  void applyVelocityAll();

 private:
  shared_ptr<std::set<shared_ptr<PhysicsComp>>> managedComponents;
};

bool areLinesIntersecting(const PositionUnit low1, const PositionUnit hi1,
                          const PositionUnit low2, const PositionUnit hi2);
