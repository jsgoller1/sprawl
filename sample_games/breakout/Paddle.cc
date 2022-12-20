#include "Paddle.hh"

Paddle::Paddle(const Vect2D& center, const int width, const int height, const std::string& texturePath)
    : Drawable(center, height, width, texturePath) {}

Paddle::~Paddle() = default;
