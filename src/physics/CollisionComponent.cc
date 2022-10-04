#include "CollisionComponent.hh"

shared_ptr<BoundingBox> CollisionComponent::getBoundingBox() const {
  return shared_ptr<BoundingBox>(new BoundingBox(
      this->positionComp->getCenter(), this->boundingBoxParams));
};

bool CollisionComponent::checkCollision(
    const shared_ptr<CollisionComponent> comp) const {
  shared_ptr<BoundingBox> usBox = this->getBoundingBox();
  shared_ptr<BoundingBox> themBox = comp->getBoundingBox();
  return usBox->checkCollision(themBox);
}

shared_ptr<Collision> CollisionComponent::getCollision() {
  // TODO: I _really_ don't want to have references to the parent object
  // stored in the physicsComponent; the physicsComponent should be constructed
  // with refs to parent-owned components it needs - if it has a direct
  // reference to the parent object, it will wind up calling the parent directly
  // and creating dependencies on it. Maybe the physicsComponent could be given
  // a callback that returns shared_ptr<GameObject> to the parent?
  // Alternatively, maybe the PhysicsManager should manage the relationships
  // between components and their parents and support turning a list of
  // PhysicsComponent into GameObjects?
}

shared_ptr<CollisionResult> CollisionComponent::resolveElasticCollision(
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
