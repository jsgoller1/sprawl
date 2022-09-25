#pragma once

#include "BoundingBox.hh"
#include "GameObject.hh"
#include "Math.hh"
#include "Memory.hh"
#include "PhysicsMgr.hh"
#include "PositionComp.hh"

// Forward decls
class PhysicsMgr;
class GameObject;

class PhysicsComp : public enable_shared_from_this<PhysicsComp> {
  // Any GameObject can have a physics component; if it does, it registers
  // it with the global PhysicsMgr.
 public:
  // ctors / dtors
  PhysicsComp(const shared_ptr<PositionComp> positionComp,
              const shared_ptr<BoundingBoxParams> BoundingBoxParams = nullptr,
              const bool collisionsSetting = false,
              const bool gravitySetting = false);
  shared_ptr<PhysicsComp> getptr() const;

  // Attribute getter/setters
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
  real getAirDragCoeff() const;
  void setAirDragCoeff(real coeff);
  real getSurfaceDragCoeff() const;
  void setSurfaceDragCoeff(real coeff);

  // Owned object getter/setters
  shared_ptr<PhysicsMgr> getManager() const;
  void setManager(const shared_ptr<PhysicsMgr> manager);
  // TODO: Do we want to use dep injection for bounding boxes?
  // Seems like we should have PhysicsComp construct them since
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
  void integrate();
  bool isMoving() const;
  bool isColliding(const shared_ptr<PhysicsComp> comp) const;

  // TODO: Physics components should probably only talk to other physics
  // components; as such, when we detect collisions, the physics manager should
  // return a list of physics components, and then we return a list of
  // gameObjects to the caller
  shared_ptr<vector<shared_ptr<GameObject>>> getCollisionObjects() const;
  // TODO: I _really_ don't want to have references to the parent object
  // stored in the physicsComponent; the physicsComponent should be constructed
  // with refs to parent-owned components it needs - if it has a direct
  // reference to the parent object, it will wind up calling the parent directly
  // and creating dependencies on it. Maybe the physicsComponent could be given
  // a callback that returns shared_ptr<GameObject> to the parent?

 private:
  // Attributes
  bool collisionsEnabled;
  bool gravityEnabled;
  real airDragCoeff;
  real surfaceDragCoeff;
  shared_ptr<Vect2D> netForce;
  shared_ptr<Vect2D> velocity;
  shared_ptr<Vect2D> acceleration;

  // Owned objects
  shared_ptr<PositionComp> positionComp;
  shared_ptr<BoundingBoxParams> boundingBoxParams;

  // References
  shared_ptr<PhysicsMgr> manager;

  // Other functionality
  void attemptMove();
  shared_ptr<Vect2D> calculateAirDragForce() const;
  shared_ptr<Vect2D> calculateSurfaceDragForce() const;
  shared_ptr<Vect2D> calculateGravityForce() const;
};
