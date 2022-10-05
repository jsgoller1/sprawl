#pragma once

#include "Memory.hh"
#include "PhysicsComponent.hh"
#include "Types.hh"

// Forward decls
class PhysicsComponent;  // see PhysicsComponent.hh

class PhysicsManager : public enable_shared_from_this<PhysicsManager> {
  // Keeps track of registered PhyiscsComponents and knows how to apply physics
  // to them

 public:
  PhysicsManager();

  std::shared_ptr<PhysicsManager> getptr();

 public:
  bool areColliding(const shared_ptr<PhysicsComponent> comp1,
                    const shared_ptr<PhysicsComponent> comp2);
  shared_ptr<vector<shared_ptr<PhysicsComponent>>> getAllColliding(
      shared_ptr<PhysicsComponent> component);
  void applyGravity(shared_ptr<PhysicsComponent> comp);
  void applyVelocity(shared_ptr<PhysicsComponent> comp);
  void applyVelocityAll();
  void manageComponent(const shared_ptr<PhysicsComponent> component);
  void unmanageComponent(const shared_ptr<PhysicsComponent> component);

 private:
  shared_ptr<set<shared_ptr<PhysicsComponent>>> managedComponents;
};

bool areLinesIntersecting(const PositionUnit low1, const PositionUnit hi1,
                          const PositionUnit low2, const PositionUnit hi2);
