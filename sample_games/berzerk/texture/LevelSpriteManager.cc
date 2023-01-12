#include "LevelSpriteManager.hh"

#include "Sprite.hh"

// TODO: Since the level sprite sheet is not a grid like the others, we implement this differently and
// directly give the coordinates on the spritesheet for the sections we want to pull (rather than using getSprite)
// TODO: Let's just modify the sprite sheets so we can use a consistent interface
LevelSpriteManager::LevelSpriteManager(const std::string& spriteSheetPath)
    : SpriteManager(spriteSheetPath, Vect2D::zero(), 0, 0, 0) {}
std::shared_ptr<Sprite> LevelSpriteManager::horizontalBorderWall() const {
  // 19,8 is the top left corner
  int topLeftX = 19;
  int topLeftY = 8;
  int wallWidth = 54;
  int wallHeight = 4;
  return std::make_shared<Sprite>(this->getSpriteSheet(), topLeftX, topLeftY, wallWidth, wallHeight);
}
std::shared_ptr<Sprite> LevelSpriteManager::verticalBorderWall() const {
  // 19,8 is the top left corner
  int topLeftX = 19;
  int topLeftY = 8;
  int wallWidth = 4;
  int wallHeight = 54;
  return std::make_shared<Sprite>(this->getSpriteSheet(), topLeftX, topLeftY, wallWidth, wallHeight);
}
std::shared_ptr<Sprite> LevelSpriteManager::horizontalInternalWall() const {
  // 19,8 is the top left corner
  int topLeftX = 24;
  int topLeftY = 75;
  int wallWidth = 44;  // -10 px; This prevents grabbing the little dark blue box in the middle
  int wallHeight = 4;
  return std::make_shared<Sprite>(this->getSpriteSheet(), topLeftX, topLeftY, wallWidth, wallHeight);
}
std::shared_ptr<Sprite> LevelSpriteManager::verticalInternalWall() const {
  // 19,8 is the top left corner
  int topLeftX = 72;
  int topLeftY = 12;
  int wallWidth = 4;
  int wallHeight = 54;
  return std::make_shared<Sprite>(this->getSpriteSheet(), topLeftX, topLeftY, wallWidth, wallHeight);
}
