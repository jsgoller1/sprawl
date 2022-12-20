#include "Brick.hh"

#include "Vect2D.hh"

Brick::Brick(const Vect2D& center, const int width, const int height, const std::string& texturePath)
    : Drawable(center, width, height, texturePath) {
  Vect2D topLeft = this->getTopLeft();
  this->_boundingBox = SDL_Rect{.x = topLeft.x, .y = topLeft.y, .w = width, .h = height};
}

Brick::~Brick() = default;

SDL_Rect Brick::getBoundingBox() const { return this->_boundingBox; }
