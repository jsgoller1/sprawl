#include "Sprite.hh"

Sprite::Sprite(SDL_Surface* spriteSheet, const int clipX, const int clipY, const int clipWidth, const int clipHeight)
    : _spriteSheet(spriteSheet) {
  this->_clipRectangle = std::unique_ptr<SDL_Rect>(new SDL_Rect{clipX, clipY, clipWidth, clipHeight});
}

SDL_Surface* Sprite::getSpriteSheet() const { return this->_spriteSheet; }

SDL_Rect* Sprite::getClipRectangle() const { return this->_clipRectangle.get(); }
