#pragma once
#include "Vect2D.hh"

class GameObject {
 public:
  virtual ~GameObject();
  // virtual Vect2D getVelocity() const;
  // virtual void setVelocity(const Vect2D& velocity);

  // virtual Vect2D getPosition() const;
  // virtual void setPosition(const Vect2D& position);

  // bool getIsMobile() const;
  // void setIsMobile(const bool setting);

  virtual void move();

 private:
  // Vect2D _velocity;
  // Vect2D _position;
  // bool _isMobile;
  // Has: Texture, SDL_Rect
};
