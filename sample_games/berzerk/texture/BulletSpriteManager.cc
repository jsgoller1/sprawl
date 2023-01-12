#include "BulletSpriteManager.hh"

#include "Sprite.hh"

constexpr int BULLET_SPRITE_WIDTH_PX = 7;
constexpr int BULLET_SPRITE_HEIGHT_PX = 7;
constexpr int BULLET_SPRITE_BOUNDARY_WIDTH_PX = 2;
const Vect2D TOP_LEFT = Vect2D::zero();

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
