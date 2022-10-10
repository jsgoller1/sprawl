#include "CollisionDetectionComponent.hh"

shared_ptr<BoundingBox> CollisionDetectionComponent::getBoundingBox() const {
  return shared_ptr<BoundingBox>(new BoundingBox(
      this->positionComponent->getCenter(), this->boundingBoxParams));
};

shared_ptr<CollisionTestResult> CollisionDetectionComponent::testCollisions(
    const shared_ptr<Vect2D> movement) {
  /*
   * Tests if a particular movement would cause an object to collide with
   * another object; this function may mutate the object's position as part of
   * testing collisions, but all mutations will be reversed.
   */

  // First, test movement on both axes to determine what collisions will
  // actually occur.
  shared_ptr<set<shared_ptr<CollisionDetectionComponent>>> trueCollisions =
      this->predictMovementCollision(movement);

  // Next, determine which collisions occurred because of single-axis movement.
  shared_ptr<set<shared_ptr<CollisionDetectionComponent>>> xCollisions =
      this->predictMovementCollision(movement->getXComponent());
  shared_ptr<set<shared_ptr<CollisionDetectionComponent>>> yCollisions =
      this->predictMovementCollision(movement->getYComponent());

  // For each of our "actual collisions", determine in what direction
  // movement was necessary to cause the collision; e.g if a collision is found
  // in both trueCollisions and xCollisions, it only required x-direction
  // movement to occur.
  shared_ptr<set<shared_ptr<Collision>>> finalizedCollisionSet =
      shared_ptr<set<shared_ptr<Collision>>>(new set<shared_ptr<Collision>>());
  for (shared_ptr<CollisionDetectionComponent> target : *trueCollisions) {
    CollisionAxis axis =
        determineCollisionAxis(target, xCollisions, yCollisions);
    shared_ptr<Collision> collision = shared_ptr<Collision>(new Collision{
        .targetIdentity = target->getOwnerIdentity(), .collisionAxis = axis});
    finalizedCollisionSet->insert(collision);
  }

  return shared_ptr<CollisionTestResult>(new CollisionTestResult(
      this->getOwnerIdentity(), movement, finalizedCollisionSet));
}

shared_ptr<set<shared_ptr<CollisionDetectionComponent>>>
CollisionDetectionComponent::predictMovementCollision(
    const shared_ptr<Vect2D> movement) {
  /*
   * Helper method; determines if a move would cause a collision by
   * performing it, testing if a collision has occurred against all relevant
   * objects, and then reversing it. Unlike testCollisions(), this function
   * treats the move as-is and doesn't test each axis separately.
   * testCollisions() uses this method for testing each axis separately.
   */
  shared_ptr<set<shared_ptr<CollisionDetectionComponent>>> targetSet =
      shared_ptr<set<shared_ptr<CollisionDetectionComponent>>>(
          new set<shared_ptr<CollisionDetectionComponent>>());

  this->positionComponent->move(movement);
  for (shared_ptr<CollisionDetectionComponent> other :
       *(this->manager->getCollisionCandidates(this->getptr()))) {
    if (this->areColliding(other)) {
      targetSet->insert(other);
    }
  }
  this->positionComponent->moveReverse(movement);

  return targetSet;
}

bool CollisionDetectionComponent::areColliding(
    /*
     * Does bounding-box test on this component and argument component
     * to determine collision.
     */
    const shared_ptr<CollisionDetectionComponent> comp) const {
  shared_ptr<BoundingBox> usBox = this->getBoundingBox();
  shared_ptr<BoundingBox> themBox = comp->getBoundingBox();
  return usBox->checkCollision(themBox);
}

CollisionAxis determineCollisionAxis(
    const shared_ptr<CollisionDetectionComponent> target,
    const shared_ptr<set<shared_ptr<CollisionDetectionComponent>>> xCollisions,
    const shared_ptr<set<shared_ptr<CollisionDetectionComponent>>>
        yCollisions) {
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
