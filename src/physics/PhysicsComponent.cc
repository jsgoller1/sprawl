#include "PhysicsComponent.hh"

// ctors / dtors
PhysicsComponent::PhysicsComponent(
    const shared_ptr<GameObjectID> ownerID,
    const shared_ptr<PositionComponent> positionComponent,
    const shared_ptr<CollisionDetectionComponent> collisionDetectionComponent,
    const bool forceResponsiveSetting, const bool gravitySetting,
    const PositionUnit maxSpeed, const PositionUnit minSpeed,
    const real dragCoefficient) {
  this->ownerID = ownerID;
  this->positionComponent = positionComponent;
  this->collisionDetectionComponent = collisionDetectionComponent;
  this->forceResponsive = forceResponsiveSetting;
  this->gravityEnabled = gravitySetting;
  this->acceleration = shared_ptr<Vect2D>(new Vect2D(0.0, 0.0));
  this->netForce = shared_ptr<Vect2D>(new Vect2D(0.0, 0.0));
  this->velocity = shared_ptr<Vect2D>(new Vect2D(0.0, 0.0));
  this->maxSpeed = maxSpeed;
  this->minSpeed = minSpeed;
  this->dragCoefficient = dragCoefficient;
}

shared_ptr<PhysicsComponent> PhysicsComponent::getptr() {
  return this->shared_from_this();
}

// Owned components/object accessors
shared_ptr<PhysicsManager> PhysicsComponent::getManager() const {
  return this->manager;
}
void PhysicsComponent::setManager(const shared_ptr<PhysicsManager> manager) {
  this->manager = manager;
};
shared_ptr<CollisionDetectionComponent>
PhysicsComponent::getCollisionDetectionComponent() const {
  return this->collisionDetectionComponent;
}
void PhysicsComponent::setCollisionDetectionComponent(
    const shared_ptr<CollisionDetectionComponent> comp) {
  this->collisionDetectionComponent = comp;
}

// Forwarding methods
bool PhysicsComponent::checkCollision(
    const shared_ptr<PhysicsComponent> comp) const {
  this->collisionDetectionComponent->checkCollision(
      comp->getCollisionDetectionComponent());
}
shared_ptr<BoundingBox> PhysicsComponent::getBoundingBox() const {
  this->collisionDetectionComponent->getBoundingBox();
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
void PhysicsComponent::integrate(const time_ms duration) {
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

  if (this->mass > 0.0 && this->getForceResponsive()) {
    this->updateVelocityFromNetForce(to_seconds(duration));
    // std::cout << "netForce: " << this->netForce->to_string() << std::endl;
    // std::cout << "Acceleration: " << this->acceleration->to_string() <<
    // std::endl;
    // std::cout << "Final Velocity: " << this->velocity->to_string() <<
    // std::endl;
    // std::cout << "----------------" << std::endl;
    const shared_ptr<Vect2D> movement = *(this->velocity) * duration;
    this->attemptMove(movement);
  }
  this->netForce = Vect2D::zero();
}

void PhysicsComponent::updateVelocityFromNetForce(const time_ms duration) {
  // Calculates velocity by imposing drag as a damper on velocity
  // rather than as a force itself.
  this->acceleration =
      calculateAcceleration(duration, this->netForce, this->mass);
  *(this->velocity) += *(calculateVelocity(duration, this->acceleration));
  real drag = pow(this->dragCoefficient, duration);
  // std::cout << "Pre-drag Velocity: " << this->velocity->to_string() <<
  // std::endl;
  *(this->velocity) *= drag;
  // std::cout << "Post-drag Velocity: " << this->velocity->to_string() <<
  // std::endl;
}

void PhysicsComponent::applyGravity() {
  if (this->getGravityEnabled()) {
    shared_ptr<Vect2D> force =
        shared_ptr<Vect2D>(new Vect2D(Direction::Down()));
    force->y *= this->getManager()->getGravityConstant();
    force->y *= this->mass;
    this->applyForce(force);
  }
};

void PhysicsComponent::attemptMove(const shared_ptr<Vect2D> movement) {
  /*
   * Attempt movement based on object's present velocity, testing for resulting
   * collisions and resolving them appropriately based on the objects
   */

  shared_ptr<CollisionTestResult> results =
      this->collisionDetectionComponent->determineCollisions(movement);
  this->positionComponent->move(results->validMove);
  this->resolveCollisions(results);
}
void PhysicsComponent::resolveCollisions(
    const shared_ptr<CollisionTestResult> result) {
  for (shared_ptr<Collision> collision : *(result->collisions)) {
    switch (collision->getType()) {
      case ELASTIC:
      case INELASTIC:
      case PARTIAL_ELASTIC:
      case PSEUDO:
        this->resolveCollisionElastic(collision);
        break;
      default:
        // Log an error
        break;
    }
  }
}

void PhysicsComponent::resolveCollisionElastic(
    const shared_ptr<Collision> collision) {
  // TODO: Since every object in Neon Rain has the same mass, we can just hack
  // elastic collisions by swapping their velocities.
  shared_ptr<PhysicsComponent> them =
      this->manager->getComponent(collision->getIdentity());
  shared_ptr<Vect2D> temp = this->velocity;
  this->velocity = them->velocity;
  them->velocity = temp;
}
