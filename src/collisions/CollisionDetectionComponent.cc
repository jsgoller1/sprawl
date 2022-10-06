#include "CollisionDetectionComponent.hh"

shared_ptr<BoundingBox> CollisionDetectionComponent::getBoundingBox() const {
  return shared_ptr<BoundingBox>(new BoundingBox(
      this->positionComponent->getCenter(), this->boundingBoxParams));
};

shared_ptr<CollisionTestResult>
CollisionDetectionComponent::determineCollisions(
    const shared_ptr<Vect2D> movement) {
  // First, test movement on both axes to determine what collisions will
  // actually occur.
  shared_ptr<CollisionTestResult> trueCollisions =
      this->predictMovementCollision(movement);

  // Next, determine which collisions occurred because of single-axis movement.
  shared_ptr<CollisionTestResult> xCollisions =
      this->predictMovementCollision(movement->getXComponent())
          ->getSharedCollisions(trueCollisions);
  shared_ptr<CollisionTestResult> yCollisions =
      this->predictMovementCollision(movement->getYComponent())
          ->getSharedCollisions(trueCollisions);

  // Collisions that result from single-axis movement during a double-axis move
  // allow for continued movement along the unaffected axis;

  // If we collided with something because of our X movement, we can continue al
}

shared_ptr<CollisionTestResult>
CollisionDetectionComponent::predictMovementCollision(
    /*
     * Determine if a move would cause a collision by performing it, testing
     * if a collision has occurred, and then reversing it.
     */
    const shared_ptr<Vect2D> movement) {
  this->positionComponent->move(movement);
  shared_ptr<CollisionTestResult> result = this->isCollision();
  this->positionComponent->moveReverse(movement);
  return result;
}

bool CollisionDetectionComponent::isCollision(
    const shared_ptr<CollisionDetectionComponent> comp) const {
  shared_ptr<BoundingBox> usBox = this->getBoundingBox();
  shared_ptr<BoundingBox> themBox = comp->getBoundingBox();
  return usBox->checkCollision(themBox);
}
