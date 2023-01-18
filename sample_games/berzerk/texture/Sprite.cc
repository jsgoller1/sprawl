#include "Sprite.hh"

Sprite::Sprite(SDL_Surface* spriteSheet, const int clipX, const int clipY, const int clipWidth, const int clipHeight)
    : Sprite(spriteSheet, clipX, clipY, clipWidth, clipHeight, 0xff, 0xff, 0xff) {}

Sprite::Sprite(SDL_Surface* spriteSheet, const int clipX, const int clipY, const int clipWidth, const int clipHeight,
               const Uint8 colorMaskRed, const Uint8 colorMaskGreen, const Uint8 colorMaskBlue)
    : _spriteSheet(spriteSheet),
      _colorMaskRed(colorMaskRed),
      _colorMaskGreen(colorMaskGreen),
      _colorMaskBlue(colorMaskBlue) {
  this->_clipRectangle = std::unique_ptr<SDL_Rect>(new SDL_Rect{clipX, clipY, clipWidth, clipHeight});
}

SDL_Surface* Sprite::getSpriteSheet() const { return this->_spriteSheet; }

SDL_Rect* Sprite::getClipRectangle() const { return this->_clipRectangle.get(); }

Uint8 Sprite::getColorMask(const ColorMaskChannel& channel) const {
  switch (channel) {
    case ColorMaskChannel::RED:
      return this->_colorMaskRed;
    case ColorMaskChannel::GREEN:
      return this->_colorMaskGreen;
    case ColorMaskChannel::BLUE:
      return this->_colorMaskBlue;
  }
}
void Sprite::setColorMask(const ColorMaskChannel& channel, const Uint8 maskValue) {
  switch (channel) {
    case ColorMaskChannel::RED:
      this->_colorMaskRed = maskValue;
      break;
    case ColorMaskChannel::GREEN:
      this->_colorMaskGreen = maskValue;
      break;
    case ColorMaskChannel::BLUE:
      this->_colorMaskBlue = maskValue;
      break;
  }
}
