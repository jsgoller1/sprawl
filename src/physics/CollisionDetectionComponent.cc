#include "CollisionDetectionComponent.hh"

shared_ptr<BoundingBox> CollisionDetectionComponent::getBoundingBox() const {
  return shared_ptr<BoundingBox>(new BoundingBox(
      this->positionComp->getCenter(), this->boundingBoxParams));
};

bool CollisionDetectionComponent::isColliding(
    const shared_ptr<CollisionDetectionComponent> comp) const {
  shared_ptr<BoundingBox> usBox = this->getBoundingBox();
  shared_ptr<BoundingBox> themBox = comp->getBoundingBox();
  return usBox->checkCollision(themBox);
}
