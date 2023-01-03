#pragma once
#include <SDL2/SDL.h>

#include <memory>
#include <string>

#include "Sprite.hh"
#include "Vect2D.hh"

class SpriteManager {
 public:
  SpriteManager(const std::string& spriteSheetPath);
  ~SpriteManager();
  SDL_Surface* getSpriteSheet() const;

 private:
  SDL_Surface* _spriteSheet;
};
