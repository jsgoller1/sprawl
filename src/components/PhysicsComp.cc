#include "PhysicsComp.hh"

PhysicsComp::PhysicsComp(const shared_ptr<PositionComp> positionComp,
                         const shared_ptr<BoundingBoxParams> boundingBoxParams,
                         const bool collisionsSetting,
                         const bool gravitySetting) {
  this->positionComp = positionComp;
  this->boundingBoxParams = boundingBoxParams;
  this->gravityEnabled = gravitySetting;
  this->collisionsEnabled = collisionsSetting;
  this->velocity = shared_ptr<Vect2D>(new Vect2D(0.0, 0.0));
}

shared_ptr<PhysicsComp> PhysicsComp::getptr() {
  return this->shared_from_this();
}

bool PhysicsComp::isForceResponsive() const { return this->forceResponsive; }
void PhysicsComp::setForceResponsive(const bool setting) {
  this->forceResponsive = setting;
}
bool PhysicsComp::hasCollisions() const { return this->collisionsEnabled; }
void PhysicsComp::enableCollisions(const bool setting) {
  this->collisionsEnabled = setting;
}
bool PhysicsComp::hasGravity() const { return this->gravityEnabled; }
void PhysicsComp::enableGravity(const bool setting) {
  this->gravityEnabled = setting;
}
shared_ptr<Vect2D> PhysicsComp::getNetForce() const { return this->netForce; }
shared_ptr<Vect2D> PhysicsComp::getVelocity() const { return this->velocity; }
shared_ptr<Vect2D> PhysicsComp::getAcceleration() const {
  return this->acceleration;
}
real PhysicsComp::getAirDragCoeff() const { return this->airDragCoeff; };
void PhysicsComp::setAirDragCoeff(real coeff) { this->airDragCoeff = coeff; };
real PhysicsComp::getSurfaceDragCoeff() const {
  return this->surfaceDragCoeff;
};
void PhysicsComp::setSurfaceDragCoeff(real coeff) {
  this->surfaceDragCoeff = coeff;
};
shared_ptr<PhysicsMgr> PhysicsComp::getManager() const { return this->manager; }
void PhysicsComp::setManager(const shared_ptr<PhysicsMgr> manager) {
  this->manager = manager;
}
shared_ptr<BoundingBoxParams> PhysicsComp::getBoundingBoxParams() const {
  return this->boundingBoxParams;
}
void PhysicsComp::setBoundingBoxParams(
    const shared_ptr<BoundingBoxParams> params) {
  this->boundingBoxParams = params;
}

shared_ptr<BoundingBox> PhysicsComp::getBoundingBox() const {
  return shared_ptr<BoundingBox>(new BoundingBox(this->boundingBoxParams));
};

void PhysicsComp::applyForce(const shared_ptr<const Vect2D> force) {
  *(this->netForce) += *force;
}

bool PhysicsComp::isMoving() const {
  // TODO: We need to do smart / precise floating point comparisons, probably
  // by defining a Velocity class that knows how to tell if two velocities are
  // close enough to be equal.
  return false;
}

bool PhysicsComp::checkCollision(const shared_ptr<PhysicsComp> comp) const {
  shared_ptr<BoundingBox> usBox =
      shared_ptr<BoundingBox>(new BoundingBox(this->boundingBoxParams));
  shared_ptr<BoundingBox> themBox =
      shared_ptr<BoundingBox>(new BoundingBox(comp->boundingBoxParams));
  return usBox->checkCollision(themBox);
}

shared_ptr<CollisionResult> PhysicsComp::resolveElasticCollision(
    shared_ptr<PhysicsComp> collisionTarget, const CollisionAxes axes,
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

void PhysicsComp::integrate(const time duration) {
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

  if (this->mass <= 0 or duration <= 0) {
    return;
  }
  if (this->isForceResponsive()) {
    this->attemptMove(duration);
    this->acceleration->addScaledVector(*(this->netForce), (1.0 / this->mass));
    // TODO: to avoid "sliding", we should probably impose a minimum velocity
    // and round any velocity below that to zero.
    this->velocity->addScaledVector(this->acceleration, duration);
  }
  this->netForce = Vect2D::zero();
}

void PhysicsComp::attemptMove(const time duration) {
  // Attempt movement based on velocity based on
  // object's velocity over the duration;
  // we will scale the velocity vector based on time
  // and add that to position, taking collisions into account

  // TODO: If a collision occurs, we should attempt to move as close to the
  // object as possible (to prevent "forcefields"); maybe add a
  // collisionDistance() that knows the closest we can get to its bounding
  // box? There are some edge cases where a move might collide with two
  // things, one of which is closer.

  shared_ptr<Vect2D> moveDistance = *(this->velocity) * duration;

  this->positionComp->moveOnlyX(moveDistance);
  shared_ptr<CollisionObjects> xCollisions = this->getCollisionObjects();
  this->positionComp->reverseMoveOnlyX(moveDistance);

  this->positionComp->moveOnlyY(moveDistance);
  shared_ptr<CollisionObjects> yCollisions = this->getCollisionObjects();
  this->positionComp->reverseMoveOnlyY(moveDistance);

  shared_ptr<CollisionObjects> doubleCollisions =
      xCollisions->getMerged(yCollisions);
  shared_ptr<CollisionObjects> xOnlyCollisions =
      xCollisions->getRemoved(yCollisions);
  shared_ptr<CollisionObjects> yOnlyCollisions =
      yCollisions->getRemoved(xCollisions);

  /*
    NOTE: If we collide with multiple objects with once, how much force we wind
    up applying to each (and them in response to us) will depend on the masses
    of the objects, the order we collide with them with, etc. In reality, most
    objects are rarely going to collide with more than one or two objects at a
    time. Some possible scenarios:
    - Character jumps/flies into or lands in a corner; collides with two objects
    who combined make up the corner.
    - Very large enemy walks into area where they collide with two characters.

    So for a "close enough" approach, we're just going to apply the same force
    to each object we collide with, and then have them all apply their forces
    back to us. Doing collisions this way should never result in having
    sufficient force to accelerate opposite the direction of the surface
    normals, so should that occur, we just zero our net force (which will cause
    integrate() to zero our velocity and acceleration).
  */
  shared_ptr<Vect2D> currentNetForce = this->getNetForce();

  for (shared_ptr<PhysicsComp> comp : *doubleCollisions->getAll()) {
    this->resolveElasticCollision(comp);
  }
  for (shared_ptr<PhysicsComp> comp : *xOnlyCollisions->getAll()) {
    this->resolveElasticCollision(comp);
  }
  for (shared_ptr<PhysicsComp> comp : *yOnlyCollisions->getAll()) {
    this->resolveElasticCollision(comp);
  }
  // TODO: If we wind up with forces causing backwards acceleration, zero them
  // here.

  // TODO: Check if we're colliding down; if so, we can jump again.
}
