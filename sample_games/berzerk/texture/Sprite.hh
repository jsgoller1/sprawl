#pragma once

#include <SDL2/SDL.h>

#include <memory>

enum class ColorMaskChannel { RED, GREEN, BLUE };

class Sprite {
 public:
  // This is a wrapper around the SDL_Surface type that can be used with smart pointers. Do not try to manually
  // delete it with SDL_FreeSurface(); call its destructor instead.

  Sprite(SDL_Surface* spriteSheet, const int clipX, const int clipY, const int clipWidth, const int clipHeight);
  Sprite(SDL_Surface* spriteSheet, const int clipX, const int clipY, const int clipWidth, const int clipHeight,
         const Uint8 colorMaskRed, const Uint8 colorMaskGreen, const Uint8 colorMaskBlue);
  SDL_Surface* getSpriteSheet() const;
  SDL_Rect* getClipRectangle() const;

  Uint8 getColorMask(const ColorMaskChannel& channel) const;
  void setColorMask(const ColorMaskChannel& channel, const Uint8 maskValue);

 private:
  SDL_Surface* _spriteSheet;
  std::unique_ptr<SDL_Rect> _clipRectangle;
  Uint8 _colorMaskRed = 0xff;
  Uint8 _colorMaskGreen = 0xff;
  Uint8 _colorMaskBlue = 0xff;
};
