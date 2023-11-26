#include "RealisticPhysicsComponent.hh"

#include "Actor.hh"

// ctors / dtors
RealisticPhysicsComponent::RealisticPhysicsComponent(const std::weak_ptr<Actor> owner,
                                                     const bool forceResponsiveSetting, const bool gravitySetting,
                                                     const PositionUnit maxSpeed, const PositionUnit minSpeed,
                                                     const DragType dragType, const real dragCoefficient,
                                                     Vect2D velocity)
    : PhysicsComponent(owner, maxSpeed, minSpeed, velocity),
      _forceResponsive(forceResponsiveSetting),
      _gravityEnabled(gravitySetting),
      _dragCoefficient(dragCoefficient),
      _dragType(dragType) {}

RealisticPhysicsComponent::~RealisticPhysicsComponent() = default;

std::string RealisticPhysicsComponent::toString() const {
  return fmt::format("RealisticPhysicsComponent({})", this->getOwner()->toString());
}

// Unique attribute accessors
bool RealisticPhysicsComponent::forceEnabled() const { return this->_forceResponsive; }
void RealisticPhysicsComponent::forceEnabled(const bool setting) { this->_forceResponsive = setting; }

bool RealisticPhysicsComponent::gravityEnabled() const { return this->_gravityEnabled; }
void RealisticPhysicsComponent::gravityEnabled(const bool setting) { this->_gravityEnabled = setting; }

DragType RealisticPhysicsComponent::dragType() const { return this->_dragType; }
void RealisticPhysicsComponent::dragType(const DragType dragType) { this->_dragType = dragType; }
real RealisticPhysicsComponent::dragCoefficient() const { return this->_dragCoefficient; }
void RealisticPhysicsComponent::dragCoefficient(const real dragCoefficient) {
  this->_dragCoefficient = dragCoefficient;
}
real RealisticPhysicsComponent::mass() const { return this->_mass; }
void RealisticPhysicsComponent::mass(const real mass) { this->_mass = mass; }
Vect2D RealisticPhysicsComponent::netForce() const { return this->_netForce; }
Vect2D RealisticPhysicsComponent::acceleration() const { return this->_acceleration; }

// Unique public methods
void RealisticPhysicsComponent::applyForce(const Vect2D& force) {
  if (this->_forceResponsive) {
    this->_netForce += force;
  }
}
Vect2D RealisticPhysicsComponent::integrate(const time_ms duration) {
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
    // TODO: Applying gravity is broken at the moment; there is some nasty coupling between collision detection
    // and physics code that I haven't worked out yet.
    // if (this->gravityEnabled() &&
    //     collisionComponent->predictMovementCollisions(Vect2D(0.0, -1.0), collisionCandidates)->empty()) {
    //   physicsComponent->applyGravity(this->getGravityConstant());
    // }

    this->updateVelocityFromNetForce(duration);
    LOG_DEBUG_SYS_ENT(PHYSICS, this->toString(), "Integrating");
    LOG_DEBUG_SYS_ENT(PHYSICS, this->toString(), "netForce: {}", this->_netForce.to_string());
    LOG_DEBUG_SYS_ENT(PHYSICS, this->toString(), "Acceleration: {}", this->_acceleration.to_string());
    LOG_DEBUG_SYS_ENT(PHYSICS, this->toString(), "Final Velocity: {}", this->getVelocity().to_string());
    movement = this->getVelocity() * duration;
  }
  this->_netForce = Vect2D::zero();
  return movement;
}

void RealisticPhysicsComponent::updateVelocityFromNetForce(const time_ms duration) {
  // Calculates velocity by imposing drag as a damper on velocity
  // rather than as a force itself.
  Vect2D newVelocity = Vect2D::zero();

  this->_acceleration = calculateAcceleration(this->_netForce, this->_mass);
  newVelocity = this->getVelocity() + calculateVelocity(duration, this->_acceleration);
  real drag =
      (this->_dragType == DragType::TIME_EXPONENTIAL) ? pow(this->_dragCoefficient, duration) : this->_dragCoefficient;
  LOG_DEBUG_SYS(PHYSICS, "Pre-drag Velocity: {}", this->getVelocity().to_string());
  newVelocity *= drag;
  newVelocity.absMin(this->getMinSpeed());
  LOG_DEBUG_SYS(PHYSICS, "Post-drag Velocity: {}", newVelocity.to_string());
  this->setVelocity(newVelocity);
}

void RealisticPhysicsComponent::applyGravity(const real gravityConstant) {
  Vect2D force = toVect2D(Direction::Down());
  force.y(force.y() * gravityConstant);
  force.y(force.y() * this->_mass);
  this->applyForce(force);
};

void RealisticPhysicsComponent::resolveCollision(const Collision& collision) {
  (void)collision;
  // TODO: Physically realistic collisions are presently disabled because splitting out the PhysicsComponent
  // behavior breaks some assumptions this code makes about other objects in the world (i.e. not every object with
  // physics enabled handles physics in a physically realistic way - what happens if a SimplePhysicsComponent owner
  // collides with a RealisticPhysicsComponent owner)?
  // LOG_DEBUG_SYS(PHYSICS, "Resolving collision: {} -> {}",
  // collision.source()->getEntityID()->c_str(),
  //               collision.target()->getEntityID()->c_str());
  // CollisionResolutionType type = this->getCollisionResolutionType(collision.target()->forceEnabled());
  // switch (type) {
  //   case CollisionResolutionType::ELASTIC:
  //     this->resolveCollisionElastic(target);
  //     break;
  //   case CollisionResolutionType::INELASTIC:
  //     this->resolveCollisionInelastic(collision);
  //     break;
  //   case CollisionResolutionType::PARTIAL_ELASTIC:
  //     break;
  //   case CollisionResolutionType::PSEUDO:
  //     break;
  // }
}

CollisionResolutionType RealisticPhysicsComponent::getCollisionResolutionType(const bool isTargetForceResponsive) {
  if (this->_forceResponsive && isTargetForceResponsive) {
    return CollisionResolutionType::ELASTIC;
  } else if (this->_forceResponsive && !isTargetForceResponsive) {
    return CollisionResolutionType::INELASTIC;
  } else if (!this->_forceResponsive && isTargetForceResponsive) {
    return CollisionResolutionType::PARTIAL_ELASTIC;
  }
  return CollisionResolutionType::PSEUDO;
}

void RealisticPhysicsComponent::resolveCollisionElastic(RealisticPhysicsComponent& target) {
  // TODO: Since every object in Neon Rain has the same mass, we can just hack
  // elastic collisions by swapping their velocities.
  Vect2D temp = this->getVelocity();
  this->setVelocity(target.getVelocity());
  target.setVelocity(temp);
}

void RealisticPhysicsComponent::resolveCollisionInelastic(const Collision& collision) {
  Vect2D newVelocity = this->getVelocity();
  switch (collision.collisionAxis()) {
    case X_ONLY:
      newVelocity.x(0.0);
      break;
    case Y_ONLY:
      newVelocity.y(0.0);
      break;
    case X_AND_Y:
    case X_OR_Y:
      newVelocity.x(0.0);
      newVelocity.y(0.0);
      break;
  }
  this->setVelocity(newVelocity);
}
