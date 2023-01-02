#pragma once

#include "DrawingProxy.hh"
#include "PositionComponent.hh"
#include "Vect2D.hh"

// fwd decls
class Sprite;
class SpriteManager;

class IDrawing {
 public:
  IDrawing(PositionComponent& _positionComponent, const int height, const int width, DrawingProxy& drawingProxy);
  virtual ~IDrawing();
  int getHeight() const;
  int getWidth() const;
  Vect2D getTopLeft() const;
  DrawingProxy& getDrawingProxy();
  void draw();
  virtual std::shared_ptr<Sprite> getCurrentSprite() = 0;

 private:
  PositionComponent& _positionComponent;
  int _height;
  int _width;
  DrawingProxy& _drawingProxy;
};

class IStaticDrawing : public IDrawing {
 public:
  IStaticDrawing(PositionComponent& _positionComponent, const int height, const int width, DrawingProxy& drawingProxy,
                 const std::shared_ptr<Sprite> sprite);

  // Get the current sprite, which is the only sprite we ever use
  std::shared_ptr<Sprite> getCurrentSprite() override;

 private:
  std::shared_ptr<Sprite> _sprite;
};

class IAnimatedDrawing : public IDrawing {
 public:
  IAnimatedDrawing(PositionComponent& _positionComponent, const int height, const int width, DrawingProxy& drawingProxy,
                   const std::shared_ptr<SpriteManager> spriteManager);

  // Get the current sprite by getting the next animation
  std::shared_ptr<Sprite> getCurrentSprite() override;

 private:
  const SpriteManager& _spriteManager;
};
