#include "Ball.hh"

Ball::Ball(const Vect2D& center, const int width, const int height, const std::string& texturePath)
    : Drawable(center, width, height, texturePath) {}

Ball::~Ball() = default;
