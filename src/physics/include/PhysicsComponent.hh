#pragma once

#include "CollisionDetectionComponent.hh"
#include "CollisionTestResult.hh"
#include "Component.hh"
#include "Math.hh"
#include "Memory.hh"
#include "PhysicsHelpers.hh"
#include "PhysicsManager.hh"
#include "PositionComponent.hh"
#include "Time.hh"
#include "Types.hh"

/*
 * PhysicsComponent is a Component class that implements all physics-related
 * behavior. It knows about stuff like mass, velocity, and acceleration, and how
 * to translate that into movement of the actual GameObject it represets via
 * calls to a PositionComponent. PhysicsComps only know about other PhysicsComps
 * and the PhysicsManager; they don't know anything about the GameObject they
 * belong to, and have no way to figure out which GameObject another
 * PhysicsComponent belongs to. This is intentional and to prevent circular /
 * messy dependencies.

 * Any GameObject can have a physics component; if it does, it must be
 * registered with the global PhysicsManager for physics behavior to occur.

 * TODO: If a GameObject wants to figure out what other
 * GameObjects it collided with, it asks its PhysicsComponent, who can ask the
 * PhysicsManager and get the answer in the form of a collection of other
 * PhysicsComps. The PhysicsManager can then be asked to translate these
 * PhysicsComps into GameObjects. We should leverage polymorphism to pass a
 * (pointer to an) empty collection of (pointers to) GameObjects from the
 * GameObject to its PhysicsComponent without PhysicsComponent knowing about its
 * contents, and have PhysicsComponent pass that to PhysicsManager when
 * translating PhysicsComps into GameObjects; this way PhysicsComponent doesn't
 * need to know anything about GameObjects and GameObject doesn't know about
 * the PhysicsManager.
 */

// Forward decls
class PhysicsManager;

class PhysicsComponent : public Component {
 public:
  // ctors / dtors
  PhysicsComponent(
      const shared_ptr<Identity> ownerIdentity,
      const shared_ptr<PositionComponent> positionComp,
      const shared_ptr<CollisionDetectionComponent> collisionDetectionComponent,
      const bool forceResponsiveSetting = false,
      const bool gravitySetting = false, const PositionUnit maxSpeed = 0.0,
      const PositionUnit minSpeed = 0.0, const real dragCoefficient = 0.0);
  shared_ptr<PhysicsComponent> getptr();

  // Owned components/object accessors
  shared_ptr<PhysicsManager> getManager() const;
  void setManager(const shared_ptr<PhysicsManager> manager);
  shared_ptr<PositionComponent> getPositionComponent() const;
  void setPositionComponent(const shared_ptr<PositionComponent> comp);
  shared_ptr<CollisionDetectionComponent> getCollisionDetectionComponent()
      const;
  void setCollisionDetectionComponent(
      const shared_ptr<CollisionDetectionComponent> comp);

  // Forwarding methods
  bool checkCollision(const shared_ptr<PhysicsComponent> comp) const;
  shared_ptr<BoundingBox> getBoundingBox() const;

  // Unique attribute accessors
  bool getForceResponsive() const;
  void setForceResponsive(const bool setting);
  bool getGravityEnabled() const;
  void setGravityEnabled(const bool setting);
  PositionUnit getMaxSpeed() const;
  void setMaxSpeed(const PositionUnit maxSpeed);
  PositionUnit getMinSpeed();
  void setMinSpeed(const PositionUnit minSpeed);
  real getDragCoefficient() const;
  void setDragCoefficient(const real dragCoefficient);
  real getMass() const;
  void setMass(const real mass);

  // NOTE: netForce, Velocity, and Acceleration are never set directly;
  // use applyForce to add forces to the object. integrate() then converts
  // these to acceleration and velocity.
  shared_ptr<Vect2D> getNetForce() const;
  shared_ptr<Vect2D> getAcceleration() const;
  shared_ptr<Vect2D> getVelocity() const;

  void applyForce(const shared_ptr<const Vect2D> force);
  void applyGravity();
  void integrate(const time_ms duration);
  shared_ptr<CollisionTestResult> determineCollisions(
      const shared_ptr<Vect2D> movement);

 private:
  // Attributes
  shared_ptr<Identity> ownerIdentity;
  bool forceResponsive;
  bool gravityEnabled;
  PositionUnit maxSpeed;
  PositionUnit minSpeed;
  real dragCoefficient;
  real mass = 1.0;
  shared_ptr<Vect2D> netForce;
  shared_ptr<Vect2D> velocity;
  shared_ptr<Vect2D> acceleration;

  shared_ptr<PhysicsManager> manager;
  shared_ptr<CollisionDetectionComponent> collisionDetectionComponent;
  shared_ptr<PositionComponent> positionComponent;

  void attemptMove(const shared_ptr<Vect2D> movement);
  void updateVelocityFromNetForce(const time_ms duration);
  void resolveCollisions(const shared_ptr<CollisionTestResult> result);
  void resolveCollisionElastic(const shared_ptr<Collision> collision);
  CollisionResolutionType getCollisionResolutionType(
      const bool isTargetForceResponsive);
};
