#include "PhysicsComponent.hh"

// ctors / dtors
PhysicsComponent::PhysicsComponent(
    const shared_ptr<Identity> ownerIdentity,
    const shared_ptr<PositionComponent> positionComponent,
    const shared_ptr<CollisionComponent> collisionComponent,
    const bool forceResponsiveSetting, const bool gravitySetting,
    const PositionUnit maxSpeed, const PositionUnit minSpeed,
    const DragType dragType, const real dragCoefficient)
    : Component(ownerIdentity) {
  this->positionComponent = positionComponent;
  this->collisionComponent = collisionComponent;
  this->forceResponsive = forceResponsiveSetting;
  this->gravityEnabled = gravitySetting;
  this->acceleration = shared_ptr<Vect2D>(new Vect2D(0.0, 0.0));
  this->netForce = shared_ptr<Vect2D>(new Vect2D(0.0, 0.0));
  this->velocity = shared_ptr<Vect2D>(new Vect2D(0.0, 0.0));
  this->maxSpeed = maxSpeed;
  this->minSpeed = minSpeed;
  this->dragType = dragType;
  this->dragCoefficient = dragCoefficient;
}

shared_ptr<PhysicsComponent> PhysicsComponent::getptr() {
  return static_pointer_cast<PhysicsComponent, Component>(
      this->shared_from_this());
}

shared_ptr<PositionComponent> PhysicsComponent::getPositionComponent() const {
  return this->positionComponent;
}
void PhysicsComponent::setPositionComponent(
    const shared_ptr<PositionComponent> positionComponent) {
  this->positionComponent = positionComponent;
}

shared_ptr<CollisionComponent> PhysicsComponent::getCollisionComponent() const {
  return this->collisionComponent;
}
void PhysicsComponent::setCollisionComponent(
    const shared_ptr<CollisionComponent> comp) {
  this->collisionComponent = comp;
}

// Unique attribute accessors
bool PhysicsComponent::getForceResponsive() const {
  return this->forceResponsive;
}
void PhysicsComponent::setForceResponsive(const bool setting) {
  this->forceResponsive = setting;
}

bool PhysicsComponent::getGravityEnabled() const {
  return this->gravityEnabled;
}
void PhysicsComponent::setGravityEnabled(const bool setting) {
  this->gravityEnabled = setting;
}
PositionUnit PhysicsComponent::getMaxSpeed() const { return this->maxSpeed; }
void PhysicsComponent::setMaxSpeed(const PositionUnit maxSpeed) {
  this->maxSpeed = maxSpeed;
}
PositionUnit PhysicsComponent::getMinSpeed() { return this->minSpeed; }
void PhysicsComponent::setMinSpeed(const PositionUnit minSpeed) {
  this->minSpeed = minSpeed;
}
DragType PhysicsComponent::getDragType() const { return this->dragType; }
void PhysicsComponent::setDragType(const DragType dragType) {
  this->dragType = dragType;
}
real PhysicsComponent::getDragCoefficient() const {
  return this->dragCoefficient;
}
void PhysicsComponent::setDragCoefficient(const real dragCoefficient) {
  this->dragCoefficient = dragCoefficient;
}
real PhysicsComponent::getMass() const { return this->mass; }
void PhysicsComponent::setMass(const real mass) { this->mass = mass; }
shared_ptr<Vect2D> PhysicsComponent::getNetForce() const {
  return this->netForce;
}
shared_ptr<Vect2D> PhysicsComponent::getAcceleration() const {
  return this->acceleration;
}
shared_ptr<Vect2D> PhysicsComponent::getVelocity() const {
  return this->velocity;
}

// Unique public methods
void PhysicsComponent::applyForce(const shared_ptr<const Vect2D> force) {
  if (this->forceResponsive) {
    *(this->netForce) += *force;
  }
}
shared_ptr<Vect2D> PhysicsComponent::integrate(const time_ms duration) {
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

  if (duration <= 0) {
    return;
  }
  shared_ptr<Vect2D> movement = Vect2D::zero();
  if (this->mass > 0.0 && this->getForceResponsive()) {
    this->updateVelocityFromNetForce(duration);
    // cout << "netForce: " << this->netForce->to_string() << endl;
    // cout << "Acceleration: " << this->acceleration->to_string() <<
    // endl;
    // cout << "Final Velocity: " << this->velocity->to_string() <<
    // endl;
    // cout << "----------------" << endl;
    movement = *(this->velocity) * duration;
  }
  this->netForce = Vect2D::zero();
  return movement;
}

void PhysicsComponent::updateVelocityFromNetForce(const time_ms duration) {
  // Calculates velocity by imposing drag as a damper on velocity
  // rather than as a force itself.
  this->acceleration =
      calculateAcceleration(duration, this->netForce, this->mass);
  *(this->velocity) += *(calculateVelocity(duration, this->acceleration));
  real drag = (this->dragType == DragType::TIME_EXPONENTIAL)
                  ? pow(this->dragCoefficient, duration)
                  : this->dragCoefficient;
  // cout << "Pre-drag Velocity: " << this->velocity->to_string() <<
  // endl;
  *(this->velocity) *= drag;
  // cout << "Post-drag Velocity: " << this->velocity->to_string() <<
  // endl;
}

void PhysicsComponent::applyGravity(const real gravityConstant) {
  if (this->getGravityEnabled()) {
    shared_ptr<Vect2D> force =
        shared_ptr<Vect2D>(new Vect2D(Direction::Down()));
    force->y *= gravityConstant;
    force->y *= this->mass;
    this->applyForce(force);
  }
};

void PhysicsComponent::resolveCollision(
    shared_ptr<Collision> collision, const CollisionResolutionType type,
    const shared_ptr<PhysicsComponent> target) {
  switch (type) {
    case CollisionResolutionType::ELASTIC:
    case CollisionResolutionType::INELASTIC:
    case CollisionResolutionType::PARTIAL_ELASTIC:
    case CollisionResolutionType::PSEUDO:
      this->resolveCollisionElastic(collision, target);
      break;
    default:
      // Log an error
      break;
  }
}

CollisionResolutionType PhysicsComponent::getCollisionResolutionType(
    const bool isTargetForceResponsive) {
  if (this->forceResponsive && isTargetForceResponsive) {
    return CollisionResolutionType::ELASTIC;
  } else if (this->forceResponsive && !isTargetForceResponsive) {
    return CollisionResolutionType::INELASTIC;
  } else if (!this->forceResponsive && isTargetForceResponsive) {
    return CollisionResolutionType::PARTIAL_ELASTIC;
  }
  return CollisionResolutionType::PSEUDO;
}

void PhysicsComponent::resolveCollisionElastic(
    const shared_ptr<Collision> collision,
    const shared_ptr<PhysicsComponent> target) {
  // TODO: Since every object in Neon Rain has the same mass, we can just hack
  // elastic collisions by swapping their velocities.
  shared_ptr<Vect2D> temp = this->velocity;
  this->velocity = target->velocity;
  target->velocity = temp;
}
