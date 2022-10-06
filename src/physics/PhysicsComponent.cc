#include "PhysicsComponent.hh"

// ctors / dtors
PhysicsComponent::PhysicsComponent(
    const shared_ptr<GameObjectID> ownerID,
    const shared_ptr<PositionComponent> positionComp,
    const shared_ptr<CollisionDetectionComponent> collisionDetectionComponent,
    const bool forceResponsiveSetting, const bool gravitySetting,
    const PositionUnit maxSpeed, const PositionUnit minSpeed,
    const real dragCoefficient) {
  this->ownerID = ownerID;
  this->positionComp = positionComp;
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
  *(this->netForce) += *force;
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
   * collisions. If movement along a particular axis would a collision, we undo
   * the move along that axis and apply resulting collision forces to each
   * object

  // TODO: If a collision occurs, should we attempt to move as close to the
  // object as possible (to prevent "forcefields"); maybe add a
  // collisionDistance() that knows the closest we can get to its bounding
  // box? There are some edge cases where a move might collide with two
  // things, one of which is closer.

  - Determine if collision occurs based on move
    - Test each axis separately, but only treat collisions happening when
      movement occurs on both axes as "true collisions"
    - When a collision occurs, we need to know which objects we collided with,
  and how far we can actually move
    - We aren't likely to collide with more than one object at a time, most
  likely 1.
  - Move to the degree possible
  - Apply resulting forces to us and each object
    - Application of forces depends on the collision type:
      - For elastic collisions, should we just swap net force? Or maybe zero our
        velocity and apply theirs as a force?
   */

  shared_ptr<CollisionTestResults> results =
      this->determineCollisions(movement);
  this->positionComp->move(results->validMovement);
  this->resolveCollisions(results);
}

shared_ptr<CollisionSet> PhysicsComponent::determineCollisions() {
  shared_ptr<CollisionDetectionComponent> cdComp =
      this->getCollisionDetectionComponent();
  this->positionComp->moveOnlyX(movement);
  shared_ptr<CollisionSet> xCollisions = cdComp->detectCollision();
  this->positionComp->reverseMoveOnlyX(movement);

  this->positionComp->moveOnlyY(movement);
  shared_ptr<CollisionSet> yCollisions = this->detectCollision();
  this->positionComp->reverseMoveOnlyY(movement);
}

void PhysicsComponent::resolveCollisions(
    const shared_ptr<Vect2D> movement,
    const shared_ptr<CollisionSet> xCollisions,
    const shared_ptr<CollisionSet> yCollisions) {
  if (xCollisions != nullptr) {
    shared_ptr<CollisionSet> xOnlyCollisions =
        xCollisions->setwiseComplement(yCollisions);
    // Resolve collisions here
  }
  if (yCollisions != nullptr) {
    shared_ptr<CollisionSet> yOnlyCollisions =
        yCollisions->setwiseComplement(xCollisions);
    // Resolve collisions here
  }
  if (xCollisions != nullptr && yCollisions != nullptr) {
    shared_ptr<CollisionSet> doubleCollisions =
        xCollisions->setwiseAnd(yCollisions);
    // Resolve collisions here
  }
}

void PhysicsComponent::resolveCollisionsElastic(
    shared_ptr<CollisionSet> collisionTarget, const CollisionAxes axes) {
  /*
    shared_ptr<CollisionResult> resolveElasticCollision(
        shared_ptr<CollisionDetectionComponent> collisionTarget,
        const CollisionAxes axes, const bool applyResultToUs,
        const bool applyResultToThem);

  */

  // Resolve a collision that we know occurred betwen us and another
  // physics-enabled object.

  // The collision is elastic, so kinetic energy and momentum will be
  //  preserved (https://en.wikipedia.org/wiki/Elastic_collision#Equations).
  //  CollisionSet axes determine whether we collided with them via X-axis
  //  movement, Y-axis movement, or both. We calculate what force they should
  //  apply to us, and what force we should apply to them. Flags control whether
  //  these are added to our/their net force. Regardless of whether we apply
  //  these forces or not, return a (pointer to a) pair of forces where
  //  pair->first is their force on us, and pair->second is our force on them.

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
  shared_ptr<CollisionDetectionComponent> us =
      this->collisionDetectionComponent;

  bool DONT_APPLY_TO_US = false;
  bool APPLY_TO_THEM = true;
  for (shared_ptr<PhysicsComponent> physComp : *doubleCollisions->getAll()) {
    shared_ptr<CollisionDetectionComponent> them =
        physComp->getCollisionDetectionComponent();
    result = us->resolveElasticCollision(them, CollisionAxes::X_AND_Y,
                                         DONT_APPLY_TO_US, APPLY_TO_THEM);
  }
  for (shared_ptr<PhysicsComponent> physComp : *xOnlyCollisions->getAll()) {
    shared_ptr<CollisionDetectionComponent> them =
        physComp->getCollisionDetectionComponent();
    result = us->resolveElasticCollision(them, CollisionAxes::X_ONLY,
                                         DONT_APPLY_TO_US, APPLY_TO_THEM);
  }
  for (shared_ptr<PhysicsComponent> physComp : *yOnlyCollisions->getAll()) {
    shared_ptr<CollisionDetectionComponent> them =
        physComp->getCollisionDetectionComponent();
    result = us->resolveElasticCollision(them, CollisionAxes::Y_ONLY,
                                         DONT_APPLY_TO_US, APPLY_TO_THEM);
  }
  // TODO: If we wind up with forces causing backwards acceleration, zero them
  // here.

  // TODO: Check if we're colliding down; if so, we can jump again.
}
