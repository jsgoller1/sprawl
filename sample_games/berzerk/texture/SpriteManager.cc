#include "SpriteManager.hh"

#include "SDL2/SDL_image.h"

SpriteManager::SpriteManager(const std::string& spriteSheetPath) {
  this->_spriteSheet = IMG_Load(spriteSheetPath.c_str());
}
SpriteManager::~SpriteManager() { SDL_FreeSurface(this->_spriteSheet); }

SDL_Surface* SpriteManager::getSpriteSheet() const { return this->_spriteSheet; }
