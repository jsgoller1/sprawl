#pragma once

#include "Collision.hh"
#include "CollisionComponent.hh"
#include "Component.hh"
#include "Math.hh"
#include "Memory.hh"
#include "PhysicsHelpers.hh"
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
  PhysicsComponent(const shared_ptr<Identity> ownerIdentity, const bool forceResponsiveSetting = false,
                   const bool gravitySetting = false, const PositionUnit maxSpeed = 0.0,
                   const PositionUnit minSpeed = 0.0, const DragType dragType = DragType::TIME_EXPONENTIAL,
                   const real dragCoefficient = 0.0);
  shared_ptr<PhysicsComponent> getptr();

  // Forwarding methods
  bool checkCollision(const PhysicsComponent& comp) const;
  BoundingBox getBoundingBox() const;

  // Unique attribute accessors
  bool forceEnabled() const;
  void forceEnabled(const bool setting);
  bool gravityEnabled() const;
  void gravityEnabled(const bool setting);
  PositionUnit maxSpeed() const;
  void maxSpeed(const PositionUnit maxSpeed);
  PositionUnit minSpeed();
  void minSpeed(const PositionUnit minSpeed);
  DragType dragType() const;
  void dragType(const DragType dragCoefficient);
  real dragCoefficient() const;
  void dragCoefficient(const real dragCoefficient);
  real mass() const;
  void mass(const real mass);

  // NOTE: netForce, Velocity, and Acceleration are never set directly;
  // use applyForce to add forces to the object. integrate() then converts
  // these to acceleration and velocity.
  Vect2D netForce() const;
  Vect2D acceleration() const;
  Vect2D velocity() const;

  void applyForce(const Vect2D& force);
  void applyGravity(const real gravityConstant);
  Vect2D integrate(const time_ms duration);
  CollisionResolutionType getCollisionResolutionType(const bool isTargetForceResponsive);
  void resolveCollision(const Collision& collision, const CollisionResolutionType type, PhysicsComponent& target);

 private:
  // Attributes
  shared_ptr<PhysicsManager> _manager;

  bool _forceResponsive;
  bool _gravityEnabled;
  PositionUnit _maxSpeed;
  PositionUnit _minSpeed;
  real _dragCoefficient;
  DragType _dragType;
  real _mass = 1.0;
  Vect2D _acceleration = Vect2D::zero();
  Vect2D _velocity = Vect2D::zero();
  Vect2D _netForce = Vect2D::zero();

  void updateVelocityFromNetForce(const time_ms duration);
  void resolveCollisionElastic(PhysicsComponent& target);
  void resolveCollisionInelastic(const Collision& collision);
};
