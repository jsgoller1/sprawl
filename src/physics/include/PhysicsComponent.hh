#pragma once

#include "BoundingBox.hh"
#include "CollidingPhysicsComponents.hh"
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
class CollidingPhysicsComponents;

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
  shared_ptr<PhysicsComponent> getptr();

  // Attribute getter/setters
  bool isForceResponsive() const;
  void setForceResponsive(const bool setting);
  bool hasCollisions() const;
  void enableCollisions(const bool setting);
  bool hasGravity() const;
  void enableGravity(const bool setting);
  // NOTE: NetForce, Velocty, and Acceleration
  // should typically not be set directly; they are inferred from
  // the net force set via applyForce(); if we want to mutate these
  // directly, we should do so through protected methods so we can control
  // how they affect the standard use-path via applyForce
  shared_ptr<Vect2D> getNetForce() const;
  shared_ptr<Vect2D> getVelocity() const;
  shared_ptr<Vect2D> getAcceleration() const;
  void setMaxSpeed(const PositionUnit maxSpeed) { this->maxSpeed = maxSpeed; }
  PositionUnit getMaxSpeed() { return this->maxSpeed; }
  void setMinSpeed(const PositionUnit minSpeed) { this->minSpeed = minSpeed; }
  PositionUnit getMinSpeed() { return this->minSpeed; }
  void setDragCoefficient(const real dragCoefficient) {
    this->dragCoefficient = dragCoefficient;
  }
  real getDragCoefficient() { return this->dragCoefficient; }

  // Owned object getter/setters
  shared_ptr<PhysicsManager> getManager() const;
  void setManager(const shared_ptr<PhysicsManager> manager);
  // TODO: Do we want to use dep injection for bounding boxes?
  // Seems like we should have PhysicsComponent construct them since
  // they need to know its center.
  shared_ptr<BoundingBoxParams> getBoundingBoxParams() const;
  void setBoundingBoxParams(const shared_ptr<BoundingBoxParams> params);

  // Forwarding methods for owned objects
  // TODO: Thinking these should be private,
  // but if so, we don't need forwarding methods
  // and can just used composed objects directly.
  //
  // void move(shared_ptr<Vect2D> direction);
  // shared_ptr<Vect2D> getCenter() const;

  // Unique/Purpose-related functionality
  shared_ptr<BoundingBox> getBoundingBox() const;
  void applyForce(const shared_ptr<const Vect2D> force);
  bool isMidair() const { return false; }
  bool isMoving() const;
  bool isColliding() const;
  bool checkCollision(const shared_ptr<PhysicsComponent> comp) const;
  void integrate(const time_ms duration);

  shared_ptr<CollidingPhysicsComponents> getCollisionObjects();
  // TODO: I _really_ don't want to have references to the parent object
  // stored in the physicsComponent; the physicsComponent should be constructed
  // with refs to parent-owned components it needs - if it has a direct
  // reference to the parent object, it will wind up calling the parent directly
  // and creating dependencies on it. Maybe the physicsComponent could be given
  // a callback that returns shared_ptr<GameObject> to the parent?
  // Alternatively, maybe the PhysicsManager should manage the relationships
  // between components and their parents and support turning a list of
  // PhysicsComponent into GameObjects?

 protected:
  // Other functionality
  void updateVelocityNoDrag(const time_ms duration);
  void updateVelocityFromNetForce(const time_ms duration);
  void attemptMove(const shared_ptr<Vect2D> moveDistance);
  shared_ptr<CollisionResult> resolveElasticCollision(
      shared_ptr<PhysicsComponent> collisionTarget, const CollisionAxes type,
      const bool applyResultToUs, const bool applyResultToThem);
  shared_ptr<Vect2D> calculateGravityForce() const;

 private:
  PositionUnit maxSpeed;
  PositionUnit minSpeed;
  real dragCoefficient;

  // Attributes
  GameObjectNameSPtr ownerName;
  bool forceResponsive;
  bool collisionsEnabled;
  bool gravityEnabled;
  // TODO: Do we want to define a custom force type, or is it
  // ok to use just a Vect2D?
  shared_ptr<Vect2D> netForce;
  shared_ptr<Vect2D> velocity;
  shared_ptr<Vect2D> acceleration;
  // TODO: In the future, we may want to have objects/characters
  // of different masses. For now, we assume global unit mass to make things
  // simple.
  real mass = 1.0;

  // Owned objects
  shared_ptr<PositionComp> positionComp;
  shared_ptr<BoundingBoxParams> boundingBoxParams;

  // References
  shared_ptr<PhysicsManager> manager;
};
