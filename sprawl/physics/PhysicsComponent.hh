#pragma once

#include "Component.hh"
#include "Math.hh"
#include "PositionComponent.hh"
#include "Time.hh"

// Forward decl
class Collision;
class PhysicsManager;

class PhysicsComponent : public Component {
 public:
  PhysicsComponent(const std::weak_ptr<Actor> owner, const PositionUnit maxSpeed = 0.0,
                   const PositionUnit minSpeed = 0.0, const Vect2D velocity = Vect2D::zero());
  virtual ~PhysicsComponent() override;

  virtual PositionUnit getMaxSpeed() const;
  virtual void setMaxSpeed(const PositionUnit maxSpeed);
  virtual PositionUnit getMinSpeed();
  virtual void setMinSpeed(const PositionUnit minSpeed);
  virtual Vect2D getVelocity() const;
  virtual void setVelocity(const Vect2D& velocity);
  virtual void resolveCollision(const Collision& collision) = 0;
  virtual Vect2D integrate(const time_ms duration) = 0;

 protected:
  const PhysicsManager& getManager() const;
  void setManager(const PhysicsManager& manager);

 private:
  std::shared_ptr<const PhysicsManager> _manager;
  PositionUnit _maxSpeed;
  PositionUnit _minSpeed;
  Vect2D _velocity;
};
