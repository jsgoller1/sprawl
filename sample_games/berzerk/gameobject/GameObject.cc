#include "GameObject.hh"

#include "DrawingComponent.hh"
#include "DrawingProxy.hh"
#include "LevelShootingProxy.hh"
#include "SDL2/SDL_image.h"
#include "SpriteManager.hh"

GameObject::GameObject(const Vect2D& position, const Vect2D& velocity) : _velocity(velocity) {
  this->_positionComponent = std::unique_ptr<PositionComponent>(new PositionComponent(position));
}

GameObject::~GameObject() = default;

Vect2D GameObject::getPosition() const { return this->_positionComponent->getPosition(); }
void GameObject::setPosition(const Vect2D& position) { this->_positionComponent->setPosition(position); }

PositionComponent& GameObject::getPositionComponent() const { return *this->_positionComponent; }

// IMovement
Vect2D GameObject::getVelocity() const { return this->_velocity; }
void GameObject::setVelocity(const Vect2D& velocity) { this->_velocity = velocity; }
void GameObject::move() {
  Vect2D currentPosition = this->_positionComponent->getPosition();
  this->_positionComponent->setPosition(currentPosition + this->_velocity);
}

// TODO: This does NOT belong here; Screen knows how to turn world coordinates into Screen coordinates.
// We should probably add a ScreenCoordinateTranslator proxy object to Screen, then pass it to Level.
static Vect2D toScreenCoordinates(const Vect2D& vect) {
  Vect2D screenCoords = Vect2D(vect);
  screenCoords.y = screenCoords.y - (1100 / 2);
  screenCoords.x = screenCoords.x + (1700 / 2);
  screenCoords.y = screenCoords.y * -1;
  return screenCoords;
}

// ICollision
bool GameObject::collisionTest(const GameObject& target) const {
  Vect2D usTopLeft = toScreenCoordinates(this->getDrawingComponent().getTopLeft());
  SDL_Rect us{.x = usTopLeft.x,
              .y = usTopLeft.y,
              .w = this->getDrawingComponent().getWidth(),
              .h = this->getDrawingComponent().getHeight()};

  Vect2D themTopLeft = toScreenCoordinates(target.getDrawingComponent().getTopLeft());
  SDL_Rect them{.x = themTopLeft.x,
                .y = themTopLeft.y,
                .w = target.getDrawingComponent().getWidth(),
                .h = target.getDrawingComponent().getHeight()};
  return SDL_HasIntersection(&us, &them);
}

bool GameObject::getShouldRemove() const { return this->_shouldRemove; }
void GameObject::setShouldRemove(const bool setting) { this->_shouldRemove = setting; }
