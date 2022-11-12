#pragma once

#include <memory>

#include "CollisionComponent.hh"
#include "Entity.hh"
#include "EntityManager.hh"
#include "GameObject.hh"
#include "PhysicsComponent.hh"
#include "Time.hh"
#include "Types.hh"

// Forward decls
class PhysicsComponent;  // see PhysicsComponent.hh

class PhysicsManager : public std::enable_shared_from_this<PhysicsManager> {
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
  PhysicsManager();
  std::shared_ptr<PhysicsManager> getptr();
  void gameLoopUpdate(const time_ms duration);

  void manage(const std::shared_ptr<Identity> identity, const std::shared_ptr<PhysicsComponent> physicsComponent,
              const std::shared_ptr<PositionComponent> positionComponent,
              const std::shared_ptr<CollisionComponent> collisionComponent);
  void unmanage(const std::shared_ptr<Identity> identity);

  real getGravityConstant() const;
  void setGravityConstant(const real gravityConstant);

 private:
  typedef struct ManagementEntry {
    const std::shared_ptr<PhysicsComponent> physicsComponent;
    const std::shared_ptr<PositionComponent> positionComponent;
    const std::shared_ptr<CollisionComponent> collisionComponent;
    ManagementEntry(const std::shared_ptr<PhysicsComponent> physicsComponent,
                    const std::shared_ptr<PositionComponent> positionComponent,
                    const std::shared_ptr<CollisionComponent> collisionComponent);
  } ManagementEntry;
  std::shared_ptr<std::map<std::shared_ptr<Identity>, std::shared_ptr<ManagementEntry>>> managementEntries;

  real gravityConstant = 0.005;

  std::shared_ptr<std::set<std::shared_ptr<CollisionComponent>>> getCollisionCandidates(
      const std::shared_ptr<CollisionComponent> source) const;

  bool diagnosticNoOverlaps() const;
};
