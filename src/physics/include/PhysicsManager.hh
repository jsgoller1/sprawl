#pragma once

#include "Memory.hh"
#include "PhysicsComponent.hh"
#include "Time.hh"

/*
The PhysicsManager class handles interactions between PhysicsComponent objects.
Like a real-life manager, it doesn't know how to do anything useful - it can
only tell things it manages how to interact with each other, and it handles
their interactions with the outside world so they don't have to. It relies on
PhysicsComponent to know how to do useful stuff, and just needs to tell it when.

PhysicsManager knows about GameObjects, and how to determine which
PhysicsComponent is owned by which GameObject.

*/

// Forward decls
class PhysicsComponent;  // see PhysicsComponent.hh

class PhysicsManager : public enable_shared_from_this<PhysicsManager> {
 public:
  PhysicsManager();
  std::shared_ptr<PhysicsManager> getptr();

 public:
  void updateManagedComponents(const time_ms duration);
  shared_ptr<vector<shared_ptr<PhysicsComponent>>> getAllColliding(
      shared_ptr<PhysicsComponent> component);
  void manageComponent(const shared_ptr<PhysicsComponent> component);
  void unmanageComponent(const shared_ptr<PhysicsComponent> component);
  real getGravityConstant() const { return this->gravityConstant; }
  void setGravityConstant(const real gravityConstant) {
    this->gravityConstant = gravityConstant;
  };

 private:
  shared_ptr<std::set<shared_ptr<PhysicsComponent>>> managedComponents;
  real gravityConstant = 10.0;
};
