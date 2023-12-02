#pragma once

#include "Math.hh"
#include "PhysicsTypes.hh"
#include "PositionComponent.hh"
#include "Time.hh"

static constexpr char PHYSICS_COMPONENT_NAME[] = "PhysicsComponent";

// Forward decl
class Collision;
class PhysicsManager;

class PhysicsComponent : public Component {
 public:
  PhysicsComponent(const std::shared_ptr<Actor> owner, const bool forceResponsiveSetting = false,
                   const bool gravitySetting = false, const PositionUnit maxSpeed = 0.0,
                   const PositionUnit minSpeed = 0.0, const DragType dragType = DragType::TIME_EXPONENTIAL,
                   const real dragCoefficient = 0.0, real mass = 1.0);
  virtual ~PhysicsComponent() override;

  std::string toString() const override;

  virtual PositionUnit getMaxSpeed() const;
  virtual void setMaxSpeed(const PositionUnit maxSpeed);
  virtual PositionUnit getMinSpeed();
  virtual void setMinSpeed(const PositionUnit minSpeed);
  virtual Vect2D getVelocity() const;
  virtual void setVelocity(const Vect2D& velocity);
  virtual void resolveCollision(const Collision& collision);
  virtual Vect2D integrate(const time_ms duration);

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

 private:
  // Attributes
  bool _forceResponsive;
  bool _gravityEnabled;
  PositionUnit _maxSpeed;
  PositionUnit _minSpeed;
  real _dragCoefficient;
  DragType _dragType;

  real _mass = 1.0;
  Vect2D _velocity = Vect2D::zero();
  Vect2D _acceleration = Vect2D::zero();
  Vect2D _netForce = Vect2D::zero();

  void updateVelocityFromNetForce(const time_ms duration);
  CollisionResolutionType getCollisionResolutionType(const bool isTargetForceResponsive);
  void resolveCollisionElastic(PhysicsComponent& target);
  void resolveCollisionInelastic(const Collision& collision);
};
