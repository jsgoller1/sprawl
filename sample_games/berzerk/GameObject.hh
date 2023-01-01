#pragma once

#include <memory>

#include "SDL2/SDL.h"
#include "Vect2D.hh"

// Forward decls
class Direction;
class DrawingProxy;
class SpriteManager;
class Sprite;

/*
 * TODO: for now, we're just going to bloat GameObject with animation, collision, drawing, and movement behavior. Once
 * we figure out exactly "what needs to know what" (each of those need to know about the object's position, for
 * instance), we'll split them off into separate interface objects. Anything of these sub-behaviors that require
 * specific attributes to be initialized should have their own init method, which we will later use for the interface
 * object constructor.
 */

class GameObject {
 public:
  GameObject(const Vect2D& position, const Vect2D& velocity, const int height, const int width,
             const SpriteManager& spriteManager, DrawingProxy& drawingProxy);
  virtual ~GameObject();

  // IPosition
  void IPositionCtor(const Vect2D& position);
  virtual Vect2D getPosition() const;
  virtual void setPosition(const Vect2D& position);
  virtual void updatePosition(const Vect2D& delta);

  // IMovement
  void IMovementCtor(const Vect2D& velocity);
  virtual Vect2D getVelocity() const;
  virtual void setVelocity(const Vect2D& velocity);

  // ICollision
  // virtual ~ICollision();
  bool collisionTest(const GameObject& target) const;
  virtual void resolveCollision(GameObject& target) = 0;

  // IDrawing/IAnimation
  void IDrawingCtor();
  void IDrawingDtor();
  int getHeight() const;
  int getWidth() const;
  Vect2D getTopLeft() const;
  virtual const SpriteManager& getSpriteManager() const = 0;
  virtual std::shared_ptr<Sprite> getCurrentSprite() const = 0;
  void draw() const;

 private:
  // IPosition
  Vect2D _position = Vect2D::zero();

  // IMovement
  Vect2D _velocity = Vect2D::zero();

  // ICollision

  // IDrawing
  int _height;
  int _width;
  const SpriteManager& _spriteManager;
  DrawingProxy& _drawingProxy;

  // IAnimation
};
