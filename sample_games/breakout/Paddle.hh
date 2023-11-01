#pragma once

#include "Drawable.hh"

#define PADDLE_WIDTH 150
#define PADDLE_HEIGHT 40
#define PADDLE_TEXTURE_PATH "/Users/joshua/Code/sprawl/sample_games/breakout/textures/paddle.png"

class Paddle : public Drawable {
 public:
  Paddle(const Vect2D& center, const int width, const int height, const std::string& texturePath);
  ~Paddle() override;
};
