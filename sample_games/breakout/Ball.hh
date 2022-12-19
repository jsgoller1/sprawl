#pragma once

#include <string>

#include "Drawable.hh"
#include "Vect2D.hh"

#define BALL_RADIUS 45
#define BALL_TEXTURE_PATH "textures/ball.png"
#define BALL_START_POSITION \
  Vect2D { .x = 0, .y = 0 }

class Ball : public Drawable {
 public:
  Ball(const Vect2D& center, const int height, const int width, const std::string& texturePath);
  void move();
};
