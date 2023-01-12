#pragma once
#include <memory>

#include "BulletSpriteManager.hh"
#include "GameObject.hh"
#include "StaticDrawingComponent.hh"

constexpr int BULLET_DEFAULT_SPEED = 10;
constexpr int BULLET_DEFAULT_HEIGHT = 35;
constexpr int BULLET_DEFAULT_WIDTH = 35;

// fwd decl
class Direction;
class DrawingProxy;
class Vect2D;

class Bullet : public GameObject {
 public:
  Bullet(const Vect2D& position, const Direction& direction, DrawingProxy& drawingProxy,
         const BulletSpriteManager& bulletSpriteManager, const BulletColor color);
  void resolveCollision(GameObject& target) override;
  StaticDrawingComponent& getDrawingComponent() const override;
  void update();

 private:
  std::unique_ptr<StaticDrawingComponent> _drawingComponent;
};
