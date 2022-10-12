#pragma once

#include "CollisionComponent.hh"
#include "Entity.hh"
#include "EntityManager.hh"
#include "GameObject.hh"
#include "Memory.hh"
#include "PhysicsComponent.hh"
#include "Time.hh"
#include "Types.hh"

// Forward decls
class PhysicsComponent;  // see PhysicsComponent.hh

class PhysicsManager : public enable_shared_from_this<PhysicsManager> {
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

  void manage(const shared_ptr<Identity> identity,
              const shared_ptr<PhysicsComponent> physicsComponent,
              const shared_ptr<PositionComponent> positionComponent,
              const shared_ptr<CollisionComponent> collisionComponent);
  void unmanage(const shared_ptr<Identity> identity);

  real getGravityConstant() const { return this->gravityConstant; }
  void setGravityConstant(const real gravityConstant) {
    this->gravityConstant = gravityConstant;
  };

 private:
  typedef struct ManagementEntry {
    const shared_ptr<PhysicsComponent> physicsComponent;
    const shared_ptr<PositionComponent> positionComponent;
    const shared_ptr<CollisionComponent> collisionComponent;
    ManagementEntry(const shared_ptr<PhysicsComponent> physicsComponent,
                    const shared_ptr<PositionComponent> positionComponent,
                    const shared_ptr<CollisionComponent> collisionComponent);
  } ManagementEntry;
  shared_ptr<map<shared_ptr<Identity>, shared_ptr<ManagementEntry>>>
      managementEntries;

  real gravityConstant = 10.0;

  shared_ptr<set<shared_ptr<CollisionComponent>>> getCollisionCandidates(
      const shared_ptr<CollisionComponent> source) const;
};
