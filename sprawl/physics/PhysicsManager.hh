#pragma once

#include <memory>
#include <unordered_set>

#include "Actor.hh"
#include "CollisionComponent.hh"
#include "ComponentManager.hh"
#include "Entity.hh"
#include "Singleton.hh"
#include "Time.hh"
#include "Types.hh"

// Forward decls

class PhysicsManager : public ComponentManager, public Singleton<PhysicsManager> {
  /*
   * The PhysicsManager class handles interactions between PhysicsComponent
   * objects. Like a real-life manager, it doesn't know how to do anything
   * useful - it can only tell things it manages how to interact with each
   * other, and it handles their interactions with the outside world so they
   * don't have to. It relies on PhysicsComponent to know how to do useful
   * stuff, and just needs to tell it when or with what other components.
   *
   * NOTE: Initially, we had a CollisionDetectionManager, but it was merged into
   * PhysicsManager because: 1) Physics and Collisions are tightly related and
   * 2) neither manager did enough to exist on its own, but we need at least one
   * of them.
   */
 public:
  // Generic manager behaviors
  // TODO: We can probably factor out of this a variadic template Manager
  // class, but we don't need it until we have at least 3-4 manager systems.
  void gameLoopUpdate(const time_ms duration) override;

  real getGravityConstant() const;
  void setGravityConstant(const real gravityConstant);

  ~PhysicsManager() override;

 private:
  friend Singleton<PhysicsManager>;

  PhysicsManager();
  PhysicsManager(const PhysicsManager&) = delete;
  PhysicsManager& operator=(const PhysicsManager&) = delete;

  real gravityConstant = 0.005;

  bool diagnosticNoOverlaps() const;
};
