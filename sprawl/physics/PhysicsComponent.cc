#include "PhysicsComponent.hh"

#include "Component.hh"
#include "PhysicsHelpers.hh"
#include "PhysicsManager.hh"

// ctors / dtors
PhysicsComponent::PhysicsComponent(const bool forceResponsiveSetting, const bool gravitySetting,
                                   const PositionUnit maxSpeed, const PositionUnit minSpeed, const DragType dragType,
                                   const real dragCoefficient, real mass)
    : Component(),
      _forceResponsive(forceResponsiveSetting),
      _gravityEnabled(gravitySetting),
      _maxSpeed(maxSpeed),
      _minSpeed(minSpeed),
      _dragCoefficient(dragCoefficient),
      _dragType(dragType),
      _mass(mass) {
  PhysicsManager::instance().manage(this->getOwner());
}

PhysicsComponent::~PhysicsComponent() { PhysicsManager::instance().unmanage(this->getOwner()); }

PositionUnit PhysicsComponent::getMaxSpeed() const { return this->_maxSpeed; }
void PhysicsComponent::setMaxSpeed(const PositionUnit maxSpeed) { this->_maxSpeed = maxSpeed; }
PositionUnit PhysicsComponent::getMinSpeed() { return this->_minSpeed; }
void PhysicsComponent::setMinSpeed(const PositionUnit minSpeed) { this->_minSpeed = minSpeed; }
Vect2D PhysicsComponent::getVelocity() const { return this->_velocity; }
void PhysicsComponent::setVelocity(const Vect2D& velocity) { this->_velocity = velocity; }

std::string PhysicsComponent::toString() const {
  return fmt::format("PhysicsComponent({})", this->getOwner()->toString());
}

// Unique attribute accessors
bool PhysicsComponent::forceEnabled() const { return this->_forceResponsive; }
void PhysicsComponent::forceEnabled(const bool setting) { this->_forceResponsive = setting; }

bool PhysicsComponent::gravityEnabled() const { return this->_gravityEnabled; }
void PhysicsComponent::gravityEnabled(const bool setting) { this->_gravityEnabled = setting; }

DragType PhysicsComponent::dragType() const { return this->_dragType; }
void PhysicsComponent::dragType(const DragType dragType) { this->_dragType = dragType; }
real PhysicsComponent::dragCoefficient() const { return this->_dragCoefficient; }
void PhysicsComponent::dragCoefficient(const real dragCoefficient) { this->_dragCoefficient = dragCoefficient; }
real PhysicsComponent::mass() const { return this->_mass; }
void PhysicsComponent::mass(const real mass) { this->_mass = mass; }
Vect2D PhysicsComponent::netForce() const { return this->_netForce; }
Vect2D PhysicsComponent::acceleration() const { return this->_acceleration; }

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

void PhysicsComponent::updateVelocityFromNetForce(const time_ms duration) {
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

void PhysicsComponent::applyGravity(const real gravityConstant) {
  Vect2D force = toVect2D(Direction::Down());
  force.y(force.y() * gravityConstant);
  force.y(force.y() * this->_mass);
  this->applyForce(force);
};

void PhysicsComponent::resolveCollision(const Collision& collision) {
  (void)collision;
  // TODO: Physically realistic collisions are presently disabled because splitting out the PhysicsComponent
  // behavior breaks some assumptions this code makes about other objects in the world (i.e. not every object with
  // physics enabled handles physics in a physically realistic way - what happens if a SimplePhysicsComponent owner
  // collides with a PhysicsComponent owner)?
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
  Vect2D temp = this->getVelocity();
  this->setVelocity(target.getVelocity());
  target.setVelocity(temp);
}

void PhysicsComponent::resolveCollisionInelastic(const Collision& collision) {
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
