#include "Brick.hh"

#include "Vect2D.hh"

Brick::Brick(const Vect2D& center, const int width, const int height, const std::string& texturePath)
    : Drawable(center, width, height, texturePath) {}

Brick::~Brick() = default;
