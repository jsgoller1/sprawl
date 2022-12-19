#include "Brick.hh"

#include "Vect2D.hh"

Brick::Brick() {}

Brick::~Brick() { SDL_DestroyTexture(this->_texture;); }
