#include "PhysicsComponent.hh"

// ctors / dtors
PhysicsComponent::PhysicsComponent(const shared_ptr<Identity> ownerIdentity, const bool forceResponsiveSetting,
                                   const bool gravitySetting, const PositionUnit maxSpeed, const PositionUnit minSpeed,
                                   const DragType dragType, const real dragCoefficient)
    : Component(ownerIdentity),
      _forceResponsive(forceResponsiveSetting),
      _gravityEnabled(gravitySetting),
      _maxSpeed(maxSpeed),
      _minSpeed(minSpeed),
      _dragCoefficient(dragCoefficient),
      _dragType(dragType) {}

shared_ptr<PhysicsComponent> PhysicsComponent::getptr() {
  return static_pointer_cast<PhysicsComponent, Component>(this->shared_from_this());
}

// Unique attribute accessors
bool PhysicsComponent::forceEnabled() const { return this->_forceResponsive; }
void PhysicsComponent::forceEnabled(const bool setting) { this->_forceResponsive = setting; }

bool PhysicsComponent::gravityEnabled() const { return this->_gravityEnabled; }
void PhysicsComponent::gravityEnabled(const bool setting) { this->_gravityEnabled = setting; }
PositionUnit PhysicsComponent::maxSpeed() const { return this->_maxSpeed; }
void PhysicsComponent::maxSpeed(const PositionUnit maxSpeed) { this->_maxSpeed = maxSpeed; }
PositionUnit PhysicsComponent::minSpeed() { return this->_minSpeed; }
void PhysicsComponent::minSpeed(const PositionUnit minSpeed) { this->_minSpeed = minSpeed; }
DragType PhysicsComponent::dragType() const { return this->_dragType; }
void PhysicsComponent::dragType(const DragType dragType) { this->_dragType = dragType; }
real PhysicsComponent::dragCoefficient() const { return this->_dragCoefficient; }
void PhysicsComponent::dragCoefficient(const real dragCoefficient) { this->_dragCoefficient = dragCoefficient; }
real PhysicsComponent::mass() const { return this->_mass; }
void PhysicsComponent::mass(const real mass) { this->_mass = mass; }
Vect2D PhysicsComponent::netForce() const { return this->_netForce; }
Vect2D PhysicsComponent::acceleration() const { return this->_acceleration; }
Vect2D PhysicsComponent::velocity() const { return this->_velocity; }

// Unique public methods
void PhysicsComponent::applyForce(const Vect2D& force) {
  if (this->_forceResponsive) {
    this->_netForce += force;
  }
}
Vect2D PhysicsComponent::integrate(const time_ms duration) {
  /*
  integrate() drives an object's physics; we apply all forces to the object
  to determine its acceleration, then its velocity, and finally attempt to
  move it and see if any collisions result. Because its velocity is determined
  from its net force, and its drag force is determined by its velocity, we do
  this in two passes:
  - we first calculate a "dragless" net force to get the "dragless velocity",
  - the dragless velocity is used with the drag coefficient to get the drag
  force
  - we combine the drag force with the original net force
  - We then calulate true velocity from the new net force, and use true
  velocity to calculate position change.

  Some implementations of 2D physics implement drag by just multiplying the
  coefficient against the dragless velocity to get true velocity. We could do
  this, but it would make managing continuous movement due to user input more
  complicated.
  */
  Vect2D movement = Vect2D::zero();
  if (duration <= 0) {
    return movement;
  }
  if (this->_mass > 0.0 && this->forceEnabled()) {
    this->updateVelocityFromNetForce(duration);
    LOG_DEBUG_SYS_ENT(PHYSICS, *this->getOwnerIdentity()->getEntityID(), "Integrating");
    LOG_DEBUG_SYS_ENT(PHYSICS, *this->getOwnerIdentity()->getEntityID(), "netForce: {}", this->_netForce.to_string());
    LOG_DEBUG_SYS_ENT(PHYSICS, *this->getOwnerIdentity()->getEntityID(), "Acceleration: {}",
                      this->_acceleration.to_string());
    LOG_DEBUG_SYS_ENT(PHYSICS, *this->getOwnerIdentity()->getEntityID(), "Final Velocity: {}",
                      this->_velocity.to_string());
    movement = this->_velocity * duration;
  }
  this->_netForce = Vect2D::zero();
  return movement;
}

void PhysicsComponent::updateVelocityFromNetForce(const time_ms duration) {
  // Calculates velocity by imposing drag as a damper on velocity
  // rather than as a force itself.
  this->_acceleration = calculateAcceleration(this->_netForce, this->_mass);
  this->_velocity += calculateVelocity(duration, this->_acceleration);
  real drag =
      (this->_dragType == DragType::TIME_EXPONENTIAL) ? pow(this->_dragCoefficient, duration) : this->_dragCoefficient;
  LOG_DEBUG_SYS(PHYSICS, "Pre-drag Velocity: {}", this->_velocity.to_string());
  this->_velocity *= drag;
  this->_velocity.absMin(this->_minSpeed);
  LOG_DEBUG_SYS(PHYSICS, "Post-drag Velocity: {}", this->_velocity.to_string());
}

void PhysicsComponent::applyGravity(const real gravityConstant) {
  Vect2D force = toVect2D(Direction::Down());
  force.y(force.y() * gravityConstant);
  force.y(force.y() * this->_mass);
  this->applyForce(force);
};

void PhysicsComponent::resolveCollision(const Collision& collision, const CollisionResolutionType type,
                                        PhysicsComponent& target) {
  switch (type) {
    case CollisionResolutionType::ELASTIC:
      this->resolveCollisionElastic(target);
      break;
    case CollisionResolutionType::INELASTIC:
      this->resolveCollisionInelastic(collision);
      break;
    case CollisionResolutionType::PARTIAL_ELASTIC:
      break;
    case CollisionResolutionType::PSEUDO:
      break;
  }
}

CollisionResolutionType PhysicsComponent::getCollisionResolutionType(const bool isTargetForceResponsive) {
  if (this->_forceResponsive && isTargetForceResponsive) {
    return CollisionResolutionType::ELASTIC;
  } else if (this->_forceResponsive && !isTargetForceResponsive) {
    return CollisionResolutionType::INELASTIC;
  } else if (!this->_forceResponsive && isTargetForceResponsive) {
    return CollisionResolutionType::PARTIAL_ELASTIC;
  }
  return CollisionResolutionType::PSEUDO;
}

void PhysicsComponent::resolveCollisionElastic(PhysicsComponent& target) {
  // TODO: Since every object in Neon Rain has the same mass, we can just hack
  // elastic collisions by swapping their velocities.
  Vect2D temp = this->_velocity;
  this->_velocity = target._velocity;
  target._velocity = temp;
}

void PhysicsComponent::resolveCollisionInelastic(const Collision& collision) {
  switch (collision.collisionAxis()) {
    case X_ONLY:
      this->_velocity.x(0.0);
      break;
    case Y_ONLY:
      this->_velocity.y(0.0);
      break;
    case X_AND_Y:
    case X_OR_Y:
      this->_velocity.x(0.0);
      this->_velocity.y(0.0);
      break;
  }
}
