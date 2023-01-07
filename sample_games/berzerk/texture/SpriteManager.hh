#pragma once
#include <SDL2/SDL.h>

#include <memory>
#include <string>

#include "Vect2D.hh"

// Fwd decls
class Sprite;

class SpriteManager {
 public:
  SpriteManager(const std::string& spriteSheetPath, const Vect2D& topLeft = Vect2D::zero(), const int spriteWidthPx = 8,
                const int spriteHeightPx = 16, const int spriteBorderSize = 1);
  ~SpriteManager();
  SDL_Surface* getSpriteSheet() const;

 protected:
  std::shared_ptr<Sprite> getSprite(const int row, const int col) const;

 private:
  SDL_Surface* _spriteSheet;
  Vect2D _topLeft = Vect2D::zero();
  int _spriteWidthPx = 8;
  int _spriteHeightPx = 16;
  int _spriteBorderSizePx = 1;
};
