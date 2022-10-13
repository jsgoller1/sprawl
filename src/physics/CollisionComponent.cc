#include "CollisionComponent.hh"

CollisionComponent::CollisionComponent(
    const shared_ptr<Identity> ownerIdentity,
    const shared_ptr<PositionComponent> positionComponent,
    const shared_ptr<BoundingBoxParams> boundingBoxParams,
    const bool collisionsEnabled)
    : positionComponent(positionComponent),
      boundingBoxParams(boundingBoxParams),
      collisionsEnabled(collisionsEnabled),
      Component(ownerIdentity) {}

shared_ptr<CollisionComponent> CollisionComponent::getptr() {
  return static_pointer_cast<CollisionComponent, Component>(
      this->shared_from_this());
}

shared_ptr<BoundingBox> CollisionComponent::getBoundingBox() const {
  return shared_ptr<BoundingBox>(new BoundingBox(
      this->positionComponent->getCenter(), this->boundingBoxParams));
};

shared_ptr<CollisionTestResult> CollisionComponent::testCollisions(
    const shared_ptr<Vect2D> positionDelta,
    const shared_ptr<set<shared_ptr<CollisionComponent>>> collisionCandidates) {
  /*
   * Tests if a particular movement would cause an object to collide with
   * another object; this function may mutate the object's position as part of
   * testing collisions, but all mutations will be reversed.
   */

  // TODO: This test "pierces" objects; e.g. if the source object is moving up
  // and to the right and collides with an object at (1,1), it wouldn't cause a
  // collision with an object at (2,2) during the same move (though an elastic
  // collision could trigger one during the _next_ check). Note though that an
  // object with height of 10 moving to the left could collide with multiple
  // objects stacked on top of each other to its left, so we do need to test
  // against multiple objects, but we only need to deal with the first one/ones
  // we'd collide with.

  // First, test movement on both axes to determine what collisions will
  // actually occur.
  shared_ptr<set<shared_ptr<CollisionComponent>>> trueCollisions =
      this->predictMovementCollision(positionDelta, collisionCandidates);

  // Next, determine which collisions occurred because of single-axis movement.
  shared_ptr<set<shared_ptr<CollisionComponent>>> xCollisions =
      this->predictMovementCollision(positionDelta->getXComponent(),
                                     collisionCandidates);
  shared_ptr<set<shared_ptr<CollisionComponent>>> yCollisions =
      this->predictMovementCollision(positionDelta->getYComponent(),
                                     collisionCandidates);

  // For each of our "actual collisions", determine in what direction
  // movement was necessary to cause the collision; e.g if a collision is found
  // in both trueCollisions and xCollisions, it only required x-direction
  // movement to occur.
  shared_ptr<set<shared_ptr<Collision>>> finalizedCollisionSet =
      shared_ptr<set<shared_ptr<Collision>>>(new set<shared_ptr<Collision>>());
  for (shared_ptr<CollisionComponent> target : *trueCollisions) {
    CollisionAxis axis =
        determineCollisionAxis(target, xCollisions, yCollisions);
    shared_ptr<Collision> collision = shared_ptr<Collision>(new Collision{
        .targetIdentity = target->getOwnerIdentity(), .collisionAxis = axis});
    finalizedCollisionSet->insert(collision);
  }

  /*
    cout << *(this->getOwnerIdentity()->getEntityID())
         << ", collision count: " << to_string(finalizedCollisionSet->size())
         << endl;
         */
  return shared_ptr<CollisionTestResult>(new CollisionTestResult(
      this->getOwnerIdentity(), this->positionComponent->getCenter(),
      positionDelta, finalizedCollisionSet));
}

shared_ptr<set<shared_ptr<CollisionComponent>>>
CollisionComponent::predictMovementCollision(
    const shared_ptr<Vect2D> positionDelta,
    const shared_ptr<set<shared_ptr<CollisionComponent>>> collisionCandidates) {
  /*
   * Helper method; determines if a move would cause a collision by
   * performing it, testing if a collision has occurred against all relevant
   * objects, and then reversing it. Unlike testCollisions(), this function
   * treats the move as-is and doesn't test each axis separately.
   * testCollisions() uses this method for testing each axis separately.
   */
  shared_ptr<set<shared_ptr<CollisionComponent>>> targetSet =
      shared_ptr<set<shared_ptr<CollisionComponent>>>(
          new set<shared_ptr<CollisionComponent>>());

  this->positionComponent->move(positionDelta);
  for (shared_ptr<CollisionComponent> other : *collisionCandidates) {
    if (this->areColliding(other)) {
      targetSet->insert(other);
    }
  }
  this->positionComponent->moveReverse(positionDelta);

  return targetSet;
}

bool CollisionComponent::areColliding(
    /*
     * Does bounding-box test on this component and argument component
     * to determine collision.
     */
    const shared_ptr<CollisionComponent> comp) const {
  if (this == comp.get()) {
    // We are never colliding with ourselves
    return false;
  }
  shared_ptr<BoundingBox> usBox = this->getBoundingBox();
  shared_ptr<BoundingBox> themBox = comp->getBoundingBox();
  return usBox->checkCollision(themBox);
}

CollisionAxis CollisionComponent::determineCollisionAxis(
    const shared_ptr<CollisionComponent> target,
    const shared_ptr<set<shared_ptr<CollisionComponent>>> xCollisions,
    const shared_ptr<set<shared_ptr<CollisionComponent>>> yCollisions) {
  bool inXCollisions = (xCollisions->find(target) != xCollisions->end());
  bool inYCollisions = (xCollisions->find(target) != yCollisions->end());
  if (!inXCollisions && !inYCollisions) {
    return X_AND_Y;
  } else if (!inXCollisions && inYCollisions) {
    return Y_ONLY;
  } else if (inXCollisions && !inYCollisions) {
    return X_ONLY;
  } else {
    return X_OR_Y;
  }
}
