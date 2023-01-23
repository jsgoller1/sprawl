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
  return this->getSprite(col, row, this->_spriteWidthPx, this->_spriteHeightPx, this->_spriteBorderSizePx);
}

std::shared_ptr<Sprite> SpriteManager::getSprite(const Vect2D& topLeft, const int width, const int height) const {
  // Sprite(SDL_Surface * spriteSheet, const int clipX, const int clipY, const int clipWidth, const int clipHeight);

  return std::make_shared<Sprite>(this->getSpriteSheet(), topLeft.x, topLeft.y, width, height);
}

std::shared_ptr<Sprite> SpriteManager::getSprite(const int col, const int row, const int spriteWidthPx,
                                                 const int spriteHeightPx, const int spriteBorderSizePx) const {
  /*
   * TODO: The interface to this function is confusing. We're following x,y coordinates by doing X first, but
   * matrix form expects row before column. Pick one and be consistent.
   */

  return std::make_shared<Sprite>(
      this->getSpriteSheet(), this->_topLeft.x + (col * (spriteWidthPx + spriteBorderSizePx)),
      this->_topLeft.y + (row * (spriteHeightPx + spriteBorderSizePx)), spriteWidthPx, spriteHeightPx);
}
