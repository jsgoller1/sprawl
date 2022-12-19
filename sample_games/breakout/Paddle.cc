#include "Paddle.hh"

Paddle::Paddle(const Vect2D& center, const int height, const int width, const std::string& texturePath)
    : Drawable(center, height, width, texturePath) {}
