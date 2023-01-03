#include "PlayerSpriteManager.hh"

PlayerSpriteManager::PlayerSpriteManager(const std::string& spriteSheetPath) : SpriteManager(spriteSheetPath) {}

std::shared_ptr<Sprite> PlayerSpriteManager::standing() const {
  // bottom right at 7,16
  int topLeftX = 0;
  int topLeftY = 0;
  int wallWidth = 7;
  int wallHeight = 16;
  return std::make_shared<Sprite>(this->getSpriteSheet(), topLeftX, topLeftY, wallWidth, wallHeight);
}
