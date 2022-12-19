#include "Ball.hh"

Ball::Ball(const Vect2D& center, const int height, const int width, const std::string& texturePath)
    : Drawable(center, height, width, texturePath) {}

Ball::~Ball() = default;
