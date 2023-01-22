#pragma once
#include <SDL2/SDL.h>

#include <memory>
#include <string>

#include "Vect2D.hh"

// Fwd decls
class Sprite;

class SpriteManager {
 public:
  SpriteManager(const std::string& spriteSheetPath, const Vect2D& topLeft, const int spriteWidthPx,
                const int spriteHeightPx, const int spriteBorderSize);
  ~SpriteManager();
  SDL_Surface* getSpriteSheet() const;

 protected:
  std::shared_ptr<Sprite> getSprite(const int col, const int row) const;
  std::shared_ptr<Sprite> getSprite(const int col, const int row, const int spriteWidthPx, const int spriteHeightPx,
                                    const int spriteBorderSizePx) const;

  // private:
  SDL_Surface* _spriteSheet;
  Vect2D _topLeft;
  int _spriteWidthPx;
  int _spriteHeightPx;
  int _spriteBorderSizePx;
};
