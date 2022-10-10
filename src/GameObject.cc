#include "GameObject.hh"

void GameObject::inferBoundingBoxFromTexture() {
  shared_ptr<Texture> texture = this->drawingComponent->getTexture();
  this->collisionDetectionComponent->setBoundingBoxParams(
      shared_ptr<BoundingBoxParams>(
          new BoundingBoxParams(texture->getHeight(), texture->getWidth())));
}
