#include "GameObject.hh"

#include "DrawingProxy.hh"
#include "SDL2/SDL_image.h"
#include "ShootingProxy.hh"
#include "SpriteManager.hh"

GameObject::GameObject(const Vect2D& position, const Vect2D& velocity, const int height, const int width,
                       const SpriteManager& spriteManager, DrawingProxy& drawingProxy)
    : _position(position),
      _velocity(velocity),
      _height(height),
      _width(width),
      _spriteManager(spriteManager),
      _drawingProxy(drawingProxy) {}

GameObject::~GameObject() = default;

// IPosition
Vect2D GameObject::getPosition() const { return this->_position; }
void GameObject::setPosition(const Vect2D& center) { this->_position = center; }
void GameObject::updatePosition(const Vect2D& delta) {
  this->_position.x += delta.x;
  this->_position.y += delta.y;
}

// IMovement
Vect2D GameObject::getVelocity() const { return this->_velocity; }
void GameObject::setVelocity(const Vect2D& velocity) { this->_velocity = velocity; }

// ICollision
bool GameObject::collisionTest(const GameObject& target) const {
  // TODO: Collision testing
  (void)target;
  return false;
}

// IDrawing
void GameObject::IDrawingCtor() {
  // SDL_SetColorKey(this->_pixelData.get(), SDL_TRUE, SDL_MapRGB(this->_pixelData->format, 0xff, 0xff, 0xff));
}
int GameObject::getHeight() const { return this->_height; }
int GameObject::getWidth() const { return this->_width; }
Vect2D GameObject::getTopLeft() const {
  Vect2D topLeft = this->_position;
  topLeft.x -= this->_width / 2;
  topLeft.y += this->_height / 2;
  return topLeft;
}
// std::shared_ptr<Sprite> GameObject::getPixelData() const { return this->_pixelData; }

void GameObject::draw() const {
  this->_drawingProxy.draw(this->_position, this->_width, this->_height, this->getCurrentSprite());
}

// IAnimation

// IShooting
