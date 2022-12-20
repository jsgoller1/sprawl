#pragma once

#include <string>

#include "Drawable.hh"
#include "Vect2D.hh"

#define BALL_RADIUS 45
#define BALL_TEXTURE_PATH "/home/joshua/Code/sprawl/sample_games/breakout/textures/ball.png"

class Ball : public Drawable {
 public:
  Ball(const Vect2D& center, const int width, const int height, const std::string& texturePath);
  ~Ball() override;
};
