#pragma once

#include "Collision.hh"
#include "PhysicsComponent.hh"
#include "PhysicsHelpers.hh"
#include "Types.hh"

/*
 * RealisticPhysicsComponent is a Component class that implements all physics-related
 * behavior. It knows about stuff like mass, velocity, and acceleration, and how
 * to translate that into movement of the actual GameObject it represets via
 * calls to a PositionComponent. PhysicsComps only know about other PhysicsComps
 * and the PhysicsManager; they don't know anything about the GameObject they
 * belong to, and have no way to figure out which GameObject another
 * RealisticPhysicsComponent belongs to. This is intentional and to prevent circular /
 * messy dependencies.

 * Any GameObject can have a physics component; if it does, it must be
 * registered with the global PhysicsManager for physics behavior to occur.

 * TODO: If a GameObject wants to figure out what other
 * GameObjects it collided with, it asks its RealisticPhysicsComponent, who can ask the
 * PhysicsManager and get the answer in the form of a collection of other
 * PhysicsComps. The PhysicsManager can then be asked to translate these
 * PhysicsComps into GameObjects. We should leverage polymorphism to pass a
 * (pointer to an) empty collection of (pointers to) GameObjects from the
 * GameObject to its RealisticPhysicsComponent without RealisticPhysicsComponent knowing about its
 * contents, and have RealisticPhysicsComponent pass that to PhysicsManager when
 * translating PhysicsComps into GameObjects; this way RealisticPhysicsComponent doesn't
 * need to know anything about GameObjects and GameObject doesn't know about
 * the PhysicsManager.
 */

// Forward decls
class PhysicsManager;

class RealisticPhysicsComponent : public PhysicsComponent {
 public:
  // ctors / dtors
  RealisticPhysicsComponent(const std::shared_ptr<Identity> ownerIdentity, const bool forceResponsiveSetting = false,
                            const bool gravitySetting = false, const DragType dragType = DragType::TIME_EXPONENTIAL,
                            const real dragCoefficient = 0.0, const PositionUnit maxSpeed = 0.0,
                            const PositionUnit minSpeed = 0.0, Vect2D velocity = Vect2D::zero());
  ~RealisticPhysicsComponent() override;
  std::shared_ptr<RealisticPhysicsComponent> getptr();

  // Unique attribute accessors
  bool forceEnabled() const;
  void forceEnabled(const bool setting);
  bool gravityEnabled() const;
  void gravityEnabled(const bool setting);
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
  void applyForce(const Vect2D& force);
  void applyGravity(const real gravityConstant);

  void resolveCollision(const Collision& collision) override;
  Vect2D integrate(const time_ms duration) override;

 private:
  // Attributes
  bool _forceResponsive;
  bool _gravityEnabled;

  real _dragCoefficient;
  DragType _dragType;
  real _mass = 1.0;
  Vect2D _acceleration = Vect2D::zero();
  Vect2D _netForce = Vect2D::zero();

  void updateVelocityFromNetForce(const time_ms duration);
  CollisionResolutionType getCollisionResolutionType(const bool isTargetForceResponsive);
  void resolveCollisionElastic(RealisticPhysicsComponent& target);
  void resolveCollisionInelastic(const Collision& collision);
};
