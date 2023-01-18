#include "PlayerSpriteManager.hh"

#include <iostream>

#include "Vect2D.hh"

constexpr int PLAYER_SPRITE_WIDTH_PX = 8;
constexpr int PLAYER_SPRITE_HEIGHT_PX = 16;
constexpr int PLAYER_SPRITE_BOUNDARY_WIDTH_PX = 1;
const Vect2D TOP_LEFT = Vect2D::zero();

PlayerSpriteManager::PlayerSpriteManager(const std::string& spriteSheetPath)
    : SpriteManager(spriteSheetPath, TOP_LEFT, PLAYER_SPRITE_WIDTH_PX, PLAYER_SPRITE_HEIGHT_PX,
                    PLAYER_SPRITE_BOUNDARY_WIDTH_PX) {}

std::shared_ptr<Sprite> PlayerSpriteManager::idle() const { return this->getSprite(0, 0); }

std::shared_ptr<Sprite> PlayerSpriteManager::movingE(const int frameNo) const {
  return this->getSprite(1 + frameNo, 0);
}
std::shared_ptr<Sprite> PlayerSpriteManager::movingW(const int frameNo) const {
  return this->getSprite(1 + frameNo, 1);
}

// NOTE: These are intentionally ordered differently than in the header file to coincide
// with how they appear on the spritesheet
std::shared_ptr<Sprite> PlayerSpriteManager::shootingNE() const { return this->getSprite(0, 2); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingE() const { return this->getSprite(1, 2); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingSE() const { return this->getSprite(2, 2); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingS() const { return this->getSprite(3, 2); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingSW() const { return this->getSprite(0, 3); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingW() const { return this->getSprite(1, 3); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingNW() const { return this->getSprite(2, 3); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingN() const { return this->getSprite(3, 3); }

std::shared_ptr<Sprite> PlayerSpriteManager::dying(const int frameNo) const {
  std::cout << "Getting dying animation frame: " << frameNo << std::endl;
  // NOTE: Technically, the sprites for dying are 1px taller (height) than the character sprites. We ignore this though
  // and are fine with chopping off the bottom 1px (no one will notice/care since they transition so quickly).
  return this->getSprite(frameNo, 4);
}

std::shared_ptr<Sprite> PlayerSpriteManager::dead() const { return this->getSprite(0, 1); }
