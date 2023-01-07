#include "SpriteManager.hh"

#include <iostream>

#include "SDL2/SDL_image.h"
#include "Sprite.hh"

SpriteManager::SpriteManager(const std::string& spriteSheetPath, const Vect2D& topLeft, const int spriteWidthPx,
                             const int spriteHeightPx, const int spriteBorderSizePx)
    : _topLeft(topLeft),
      _spriteWidthPx(spriteWidthPx),
      _spriteHeightPx(spriteHeightPx),
      _spriteBorderSizePx(spriteBorderSizePx) {
  this->_spriteSheet = IMG_Load(spriteSheetPath.c_str());
}
SpriteManager::~SpriteManager() { SDL_FreeSurface(this->_spriteSheet); }

SDL_Surface* SpriteManager::getSpriteSheet() const { return this->_spriteSheet; }

std::shared_ptr<Sprite> SpriteManager::getSprite(const int col, const int row) const {
  std::cout << "x: " << this->_topLeft.x + (col * (this->_spriteWidthPx + this->_spriteBorderSizePx)) << std::endl;
  std::cout << "y: " << this->_topLeft.y + (row * (this->_spriteHeightPx + this->_spriteBorderSizePx)) << std::endl;

  return std::make_shared<Sprite>(this->getSpriteSheet(),
                                  this->_topLeft.x + (col * (this->_spriteWidthPx + this->_spriteBorderSizePx)),
                                  this->_topLeft.y + (row * (this->_spriteHeightPx + this->_spriteBorderSizePx)),
                                  this->_spriteWidthPx, this->_spriteHeightPx);
}
