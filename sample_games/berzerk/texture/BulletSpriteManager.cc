#include "BulletSpriteManager.hh"

#include "Configs.hh"
#include "Sprite.hh"

BulletSpriteManager::BulletSpriteManager(const std::string& spriteSheetPath)
    : SpriteManager(spriteSheetPath, TOP_LEFT, BULLET_SPRITE_WIDTH_PX, BULLET_SPRITE_HEIGHT_PX,
                    BULLET_SPRITE_BOUNDARY_WIDTH_PX) {}

std::shared_ptr<Sprite> BulletSpriteManager::bulletHorizontal(const BulletColor color) const {
  return this->getSprite(0, color);
}
std::shared_ptr<Sprite> BulletSpriteManager::bulletSE(const BulletColor color) const {
  return this->getSprite(1, color);
}

std::shared_ptr<Sprite> BulletSpriteManager::bulletVertical(const BulletColor color) const {
  return this->getSprite(2, color);
}
std::shared_ptr<Sprite> BulletSpriteManager::bulletNE(const BulletColor color) const {
  return this->getSprite(3, color);
}
