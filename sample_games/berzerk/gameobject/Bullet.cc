#include "Bullet.hh"

#include <iostream>

#include "Direction.hh"
#include "DrawingProxy.hh"
#include "PlayerSpriteManager.hh"
#include "Vect2D.hh"

Bullet::Bullet(const Vect2D& position, const Direction& direction, DrawingProxy& drawingProxy,
               const BulletSpriteManager& bulletSpriteManager, const BulletColor color)
    : GameObject(position, Vect2D(direction) * BULLET_DEFAULT_SPEED) {
  std::shared_ptr<Sprite> sprite;
  if (direction == Direction::SouthWest() || direction == Direction::NorthEast()) {
    sprite = bulletSpriteManager.bulletNE(color);
  } else if (direction == Direction::SouthEast() || direction == Direction::NorthWest()) {
    sprite = bulletSpriteManager.bulletSE(color);
  } else if (direction == Direction::North() || direction == Direction::South()) {
    sprite = bulletSpriteManager.bulletVertical(color);
  } else {  // direction == East or direction == West
    sprite = bulletSpriteManager.bulletHorizontal(color);
  }
  this->_drawingComponent = std::unique_ptr<StaticDrawingComponent>(new StaticDrawingComponent(
      this->getPositionComponent(), BULLET_DEFAULT_HEIGHT, BULLET_DEFAULT_WIDTH, drawingProxy, sprite));
}

void Bullet::resolveCollision(GameObject& target) {
  (void)target;
  std::cout << "Bullet collided with something at " << this->getPosition().x << "," << this->getPosition().y
            << std::endl;
  this->setShouldRemove(true);
}
StaticDrawingComponent& Bullet::getDrawingComponent() const { return *this->_drawingComponent; }

void Bullet::update() { this->move(); }
