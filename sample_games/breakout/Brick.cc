#include "Brick.hh"

#include "Vect2D.hh"

Brick::Brick(const Vect2D& center, const int height, const int width, const std::string& texturePath)
    : Drawable(center, height, width, texturePath) {}
