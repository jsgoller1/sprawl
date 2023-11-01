#pragma once

#include <string>

#include "Drawable.hh"
#include "Vect2D.hh"

#define BALL_RADIUS 45
#define BALL_TEXTURE_PATH "/Users/joshua/Code/sprawl/sample_games/breakout/textures/ball.png"

class Ball : public Drawable {
 public:
  Ball(const Vect2D& center, const int width, const int height, const std::string& texturePath);
  ~Ball() override;

  Vect2D getLeftmostPoint() const;
  Vect2D getRightmostPoint() const;
  Vect2D getTopPoint() const;
  Vect2D getBottomPoint() const;

  Vect2D getVelocity() const;
  void setVelocity(const Vect2D& velocity);

  void handleHorizontalCollision();
  void handleVerticalCollision();

 private:
  Vect2D _velocity = Vect2D{0, 10};
};
