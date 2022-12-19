#pragma once

#include "Drawable.hh"

#define PADDLE_WIDTH 150
#define PADDLE_HEIGHT 40
#define PADDLE_TEXTURE_PATH "/home/joshua/Code/sprawl/sample_games/breakout/textures/paddle.png"
#define PADDLE_START_POSITION \
  Vect2D { .x = 0, .y = 0 }

class Paddle : public Drawable {
 public:
  Paddle(const Vect2D& center, const int height, const int width, const std::string& texturePath);
  ~Paddle() override;
};
