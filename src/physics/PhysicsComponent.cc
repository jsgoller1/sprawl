#include "PhysicsComponent.hh"

PhysicsComponent::PhysicsComponent(
    const GameObjectNameSPtr ownerName,
    const shared_ptr<PositionComp> positionComp,
    const shared_ptr<BoundingBoxParams> boundingBoxParams,
    const bool forceResponsiveSetting, const bool collisionsSetting,
    const bool gravitySetting, const PositionUnit maxSpeed,
    const PositionUnit minSpeed, const real dragCoefficient) {
  this->ownerName = ownerName;
  this->positionComp = positionComp;
  this->boundingBoxParams = boundingBoxParams;
  this->forceResponsive = forceResponsiveSetting;
  this->gravityEnabled = gravitySetting;
  this->collisionsEnabled = collisionsSetting;
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

bool PhysicsComponent::isForceResponsive() const {
  return this->forceResponsive;
}
void PhysicsComponent::setForceResponsive(const bool setting) {
  this->forceResponsive = setting;
}
bool PhysicsComponent::hasCollisions() const { return this->collisionsEnabled; }
void PhysicsComponent::enableCollisions(const bool setting) {
  this->collisionsEnabled = setting;
}
bool PhysicsComponent::hasGravity() const { return this->gravityEnabled; }
void PhysicsComponent::enableGravity(const bool setting) {
  this->gravityEnabled = setting;
}
shared_ptr<Vect2D> PhysicsComponent::getNetForce() const {
  return this->netForce;
}
shared_ptr<Vect2D> PhysicsComponent::getVelocity() const {
  return this->velocity;
}
shared_ptr<Vect2D> PhysicsComponent::getAcceleration() const {
  return this->acceleration;
}

/*
real PhysicsComponent::getAirDragCoeff() const { return this->airDragCoeff; };
void PhysicsComponent::setAirDragCoeff(real coeff) {
  this->airDragCoeff = coeff;
};
real PhysicsComponent::getSurfaceDragCoeff() const {
  return this->surfaceDragCoeff;
};
void PhysicsComponent::setSurfaceDragCoeff(real coeff) {
  this->surfaceDragCoeff = coeff;
};
*/
shared_ptr<PhysicsManager> PhysicsComponent::getManager() const {
  return this->manager;
}
void PhysicsComponent::setManager(const shared_ptr<PhysicsManager> manager) {
  this->manager = manager;
}
shared_ptr<BoundingBoxParams> PhysicsComponent::getBoundingBoxParams() const {
  return this->boundingBoxParams;
}
void PhysicsComponent::setBoundingBoxParams(
    const shared_ptr<BoundingBoxParams> params) {
  this->boundingBoxParams = params;
}

shared_ptr<BoundingBox> PhysicsComponent::getBoundingBox() const {
  return shared_ptr<BoundingBox>(new BoundingBox(
      this->positionComp->getCenter(), this->boundingBoxParams));
};

void PhysicsComponent::applyForce(const shared_ptr<const Vect2D> force) {
  *(this->netForce) += *force;
}

bool PhysicsComponent::isMoving() const {
  // TODO: We need to do smart / precise floating point comparisons, probably
  // by defining a Velocity class that knows how to tell if two velocities are
  // close enough to be equal.
  return false;
}

bool PhysicsComponent::checkCollision(
    const shared_ptr<PhysicsComponent> comp) const {
  shared_ptr<BoundingBox> usBox = this->getBoundingBox();
  shared_ptr<BoundingBox> themBox = comp->getBoundingBox();
  return usBox->checkCollision(themBox);
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

  Position change is the product of our true velocity and duration. When we
  calculate position change, separately attempt to move as far as we should
  along each axis, see if a collision occurs, and reverse the move. We must test
  each axis separately, then both simultaneously to confirm our move won't
  result in a collision. Only then can the object actually be left in the final
  position.

  If a collision does occur during position change, we treat it as a
  mostly-elastic collision. Kinetic energy and momentum are preserved if both
  objects respond to force. If the object we collide with doesn't respond to
  force, our force in the direction we collided with it becomes zero (we will
  still apply force to it). This will allow for Mario style movement where
  colliding horizontally while jumping results in purely upward movement.
  */

  if (this->mass <= 0 or duration <= 0) {
    return;
  }

  this->updateVelocityNoDrag(to_seconds(duration));
  std::cout << "netForce (x): " << this->netForce->x << std::endl;
  std::cout << "Acceleration (x): " << this->acceleration->x << std::endl;
  std::cout << "Final Velocity (x): " << this->velocity->x << std::endl;
  const shared_ptr<Vect2D> moveDistance = *(this->velocity) * duration;
  this->positionComp->move(moveDistance);
  std::cout << "----------------" << std::endl;

  /*
  if (this->isForceResponsive()) {
    // - attempt to do the X/Y move, and get a list of objects we'd collide
    // with, then move back
    // - for each one, apply force based on our velocity to them, then apply
    // their normal force to us and update our velocity accordingly.
    // - Repeat this procedure for X and Y moves.
    this->attemptMove(moveDistance);
  }
  */
  this->netForce = Vect2D::zero();
}

shared_ptr<CollidingPhysicsComponents> PhysicsComponent::getCollisionObjects() {
}

void PhysicsComponent::attemptMove(const shared_ptr<Vect2D> moveDistance) {
  // Attempt movement based on velocity based on
  // object's velocity over the duration;
  // we will scale the velocity vector based on time
  // and add that to position, taking collisions into account

  // TODO: If a collision occurs, we should attempt to move as close to the
  // object as possible (to prevent "forcefields"); maybe add a
  // collisionDistance() that knows the closest we can get to its bounding
  // box? There are some edge cases where a move might collide with two
  // things, one of which is closer.

  this->positionComp->moveOnlyX(moveDistance);
  shared_ptr<CollidingPhysicsComponents> xCollisions =
      this->getCollisionObjects();
  this->positionComp->reverseMoveOnlyX(moveDistance);

  this->positionComp->moveOnlyY(moveDistance);
  shared_ptr<CollidingPhysicsComponents> yCollisions =
      this->getCollisionObjects();
  this->positionComp->reverseMoveOnlyY(moveDistance);

  shared_ptr<CollidingPhysicsComponents> doubleCollisions =
      xCollisions->getMerged(yCollisions);
  shared_ptr<CollidingPhysicsComponents> xOnlyCollisions =
      xCollisions->getRemoved(yCollisions);
  shared_ptr<CollidingPhysicsComponents> yOnlyCollisions =
      yCollisions->getRemoved(xCollisions);

  /*
    NOTE: If we collide with multiple objects with once, how much force we wind
    up applying to each (and them in response to us) should depend on the masses
    of the objects, the order we collide with them with, etc. In reality, most
    objects are rarely going to collide with more than one or two objects at a
    time. Some possible scenarios:
    - Character jumps/flies into or lands in a corner; collides with two objects
    who combined make up the corner.
    - Very large enemy walks into area where they collide with two characters.

    So for a "close enough" approach, we're just going to apply the same force
    to each object we collide with, accumulate all the opposing forces they
    would apply back to us as though we only collided into them, and then add
    that to our net force. An edge case for this can occur where the cumulative
    normal forces result in backwards acceleration; we check for this and just
    zero our net force if it would occur.

    and then have them all apply their forces
    back to us. Doing collisions this way should never result in having
    sufficient force to accelerate opposite the direction of the surface
    normals, so should that occur, we just zero our net force (which will cause
    integrate() to zero our velocity and acceleration).
  */
  shared_ptr<Vect2D> currentNetForce = this->getNetForce();
  shared_ptr<Vect2D> cumulativeNormalForce = Vect2D::zero();
  shared_ptr<CollisionResult> result;

  bool DONT_APPLY_TO_US = false;
  bool APPLY_TO_THEM = true;
  for (shared_ptr<PhysicsComponent> comp : *doubleCollisions->getAll()) {
    result = this->resolveElasticCollision(comp, CollisionAxes::X_AND_Y,
                                           DONT_APPLY_TO_US, APPLY_TO_THEM);
  }
  for (shared_ptr<PhysicsComponent> comp : *xOnlyCollisions->getAll()) {
    result = this->resolveElasticCollision(comp, CollisionAxes::X_ONLY,
                                           DONT_APPLY_TO_US, APPLY_TO_THEM);
  }
  for (shared_ptr<PhysicsComponent> comp : *yOnlyCollisions->getAll()) {
    result = this->resolveElasticCollision(comp, CollisionAxes::Y_ONLY,
                                           DONT_APPLY_TO_US, APPLY_TO_THEM);
  }
  // TODO: If we wind up with forces causing backwards acceleration, zero them
  // here.

  // TODO: Check if we're colliding down; if so, we can jump again.
}

void PhysicsComponent::updateVelocityNoDrag(const time_ms duration) {
  // Calculates velocity by imposing drag as a damper on velocity
  // rather than as a force itself.
  this->acceleration =
      calculateAcceleration(duration, this->netForce, this->mass);
  *(this->velocity) += *(calculateVelocity(duration, this->acceleration));
  real drag = pow(this->dragCoefficient, duration);
  std::cout << "Pre-drag Velocity (x): " << this->velocity->x << std::endl;
  *(this->velocity) *= drag;
  std::cout << "Post-drag Velocity (x): " << this->velocity->x << std::endl;

  // Clamp to zero; we don't want to very slowly decelerate
  // to zero, but do so more abruptly
  // this->velocity->roundToZero(this->minSpeed);
}

void PhysicsComponent::updateVelocityFromNetForce(const time_ms duration) {
  // Determine the drag force associated with our velocity,
  // add that to the net force, and get our true velocity.
  // TODO: This, combined with our "add some force" technique for user
  // movement, results in odd blitting/janky behavior.

  shared_ptr<Vect2D> draglessAcceleration =
      calculateAcceleration(duration, this->netForce, this->mass);
  shared_ptr<Vect2D> draglessVelocity =
      calculateVelocity(duration, draglessAcceleration);
  shared_ptr<Vect2D> dragForce = calculateDragForce(
      *draglessVelocity + *this->velocity, this->dragCoefficient);
  this->applyForce(dragForce);
  this->acceleration =
      calculateAcceleration(duration, this->netForce, this->mass);
  *(this->velocity) += *(calculateVelocity(duration, this->acceleration));
}

shared_ptr<CollisionResult> PhysicsComponent::resolveElasticCollision(
    shared_ptr<PhysicsComponent> collisionTarget, const CollisionAxes axes,
    const bool applyResultToUs, const bool applyResultToThem) {
  // Resolve a collision that has occurred betwen us and another physics-enabled
  // object. The collision is elastic, so kinetic energy and momentum will be
  // preserved (https://en.wikipedia.org/wiki/Elastic_collision#Equations).
  // Collision axes determine whether we collided with them via X-axis movement,
  // Y-axis movement, or both. We calculate what force they should apply to us,
  // and what force we should apply to them. Flags control whether these are
  // added to our/their net force. Regardless of whether we apply these forces
  // or not, return a (pointer to a) pair of forces where pair->first is their
  // force on us, and pair->second is our force on them.
}
