#pragma once

#include "BoundingBox.hh"
#include "CollisionComponent.hh"
#include "Math.hh"
#include "Memory.hh"
#include "PhysicsHelpers.hh"
#include "PhysicsManager.hh"
#include "PositionComp.hh"
#include "Time.hh"
#include "Types.hh"

/*
PhysicsComponent is a Component class that implements all physics-related
behavior. It knows about stuff like mass, velocity, and acceleration, and how to
translate that into movement of the actual GameObject it represets via calls to
a PositionComp. PhysicsComps only know about other PhysicsComps and the
PhysicsManager; they don't know anything about the GameObject they belong to,
and have no way to figure out which GameObject another PhysicsComponent belongs
to. This is intentional and to prevent circular / messy dependencies.

Any GameObject can have a physics component; if it does, it must be registered
with the global PhysicsManager for PhysicsBehavior to occur.

TODO: If a GameObject wants to figure out what other
GameObjects it collided with, it asks its PhysicsComponent, who can ask the
PhysicsManager and get the answer in the form of a collection of other
PhysicsComps. The PhysicsManager can then be asked to translate these
PhysicsComps into GameObjects. We should leverage polymorphism to pass a
(pointer to an) empty collection of (pointers to) GameObjects from the
GameObject to its PhysicsComponent without PhysicsComponent knowing about its
contents, and have PhysicsComponent pass that to PhysicsManager when translating
PhysicsComps into GameObjects; this way PhysicsComponent doesn't need to know
anything about GameObjects and GameObject doesn't know about the PhysicsManager.
*/

// Forward decls
class PhysicsManager;

class PhysicsComponent : public enable_shared_from_this<PhysicsComponent> {
 public:
  // ctors / dtors
  PhysicsComponent(
      const GameObjectNameSPtr ownerName,
      const shared_ptr<PositionComp> positionComp,
      const shared_ptr<BoundingBoxParams> BoundingBoxParams = nullptr,
      const bool forceResponsiveSetting = false,
      const bool collisionsSetting = false, const bool gravitySetting = false,
      const PositionUnit maxSpeed = 0.0, const PositionUnit minSpeed = 0.0,
      const real dragCoefficient = 0.0);
  shared_ptr<PhysicsComponent> getptr() { return this->shared_from_this(); }

  // Attribute getter/setters
  bool getForceResponsive() const { return this->forceResponsive; }
  void setForceResponsive(const bool setting) {
    this->forceResponsive = setting;
  }

  bool getGravityEnabled() const { return this->gravityEnabled; }
  void setGravityEnabled(const bool setting) { this->gravityEnabled = setting; }
  PositionUnit getMaxSpeed() const { return this->maxSpeed; }
  void setMaxSpeed(const PositionUnit maxSpeed) { this->maxSpeed = maxSpeed; }
  PositionUnit getMinSpeed() { return this->minSpeed; }
  void setMinSpeed(const PositionUnit minSpeed) { this->minSpeed = minSpeed; }
  real getDragCoefficient() const { return this->dragCoefficient; }
  void setDragCoefficient(const real dragCoefficient) {
    this->dragCoefficient = dragCoefficient;
  }
  real getMass() const { return this->mass; }
  void setMass(const real mass) { this->mass = mass; }

  // NOTE: netForce, Velocity, and Acceleration are never set directly;
  // use applyForce to add forces to the object. integrate() then converts
  // these to acceleration and velocity.
  shared_ptr<Vect2D> getNetForce() const { return this->netForce; }
  shared_ptr<Vect2D> getAcceleration() const { return this->acceleration; }
  shared_ptr<Vect2D> getVelocity() const { return this->velocity; }

  // Owned components/objects and forwarding methods
  shared_ptr<PhysicsManager> getManager() const { return this->manager; }
  void setManager(const shared_ptr<PhysicsManager> manager) {
    this->manager = manager;
  };
  shared_ptr<CollisionComponent> getCollisionComponent() const {
    return this->collisionComponent;
  }
  void getCollisionComponent(const shared_ptr<CollisionComponent> comp) {
    this->collisionComponent = comp;
  }
  shared_ptr<BoundingBox> getBoundingBox() {
    this->collisionComponent->getBoundingBox();
  }
  bool checkCollision(const shared_ptr<PhysicsComponent> comp) const;

  // Unique/Purpose-related functionality
  shared_ptr<BoundingBox> getBoundingBox() const;
  void applyForce(const shared_ptr<const Vect2D> force);
  void applyGravity();
  bool isMidair() const;
  bool isMoving() const;
  void integrate(const time_ms duration);

 protected:
  void attemptMove(const shared_ptr<Vect2D> moveDistance);
  shared_ptr<CollisionResult> resolveElasticCollision(
      shared_ptr<PhysicsComponent> collisionTarget, const CollisionAxes type,
      const bool applyResultToUs, const bool applyResultToThem);

 private:
  // Attributes
  GameObjectNameSPtr ownerName;
  bool forceResponsive;
  bool gravityEnabled;
  PositionUnit maxSpeed;
  PositionUnit minSpeed;
  real dragCoefficient;
  real mass;
  shared_ptr<Vect2D> netForce;
  shared_ptr<Vect2D> velocity;
  shared_ptr<Vect2D> acceleration;

  shared_ptr<PhysicsManager> manager;
  shared_ptr<CollisionComponent> collisionComponent;
  shared_ptr<PositionComp> positionComp;
  void updateVelocityFromNetForce(const time_ms duration);
};
