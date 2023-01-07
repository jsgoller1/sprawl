#include "PlayerSpriteManager.hh"

#include <iostream>

#include "Vect2D.hh"

PlayerSpriteManager::PlayerSpriteManager(const std::string& spriteSheetPath) : SpriteManager(spriteSheetPath) {}

std::shared_ptr<Sprite> PlayerSpriteManager::movingE(const int frameNo) const {
  return this->getSprite(0, 1 + frameNo);
}
std::shared_ptr<Sprite> PlayerSpriteManager::movingW(const int frameNo) const {
  return this->getSprite(1, 1 + frameNo);
}
std::shared_ptr<Sprite> PlayerSpriteManager::dying(const int frameNo) const {
  std::cout << "Getting dying animation frame: " << frameNo << std::endl;
  // NOTE: Technically, the sprites for dying are 1px taller (height) than the character sprites. We ignore this though
  // and are fine with chopping off the bottom 1px (no one will notice/care since they transition so quickly).
  return this->getSprite(frameNo, 4);
}

std::shared_ptr<Sprite> PlayerSpriteManager::shootingN() const { return this->getSprite(3, 3); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingE() const { return this->getSprite(2, 1); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingS() const { return this->getSprite(2, 3); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingW() const { return this->getSprite(3, 1); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingNE() const { return this->getSprite(2, 0); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingSE() const { return this->getSprite(2, 2); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingNW() const { return this->getSprite(3, 2); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingSW() const { return this->getSprite(3, 1); }

std::shared_ptr<Sprite> PlayerSpriteManager::standing() const { return this->getSprite(0, 0); }
