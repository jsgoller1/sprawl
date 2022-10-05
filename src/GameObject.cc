#include "GameObject.hh"

void GameObject::inferBoundingBoxFromTexture() {
  shared_ptr<Texture> texture = this->drawingComponent->getTexture();
  this->physicsComponent->setBoundingBox(texture->getHeight(),
                                         texture->getWidth());
}
