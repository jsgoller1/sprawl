#include "SpriteManager.hh"

#include "SDL2/SDL_image.h"

SpriteManager::SpriteManager(const std::string& spriteSheetPath) {
  this->_spriteSheet = IMG_Load(spriteSheetPath.c_str());
}
SpriteManager::~SpriteManager() { SDL_FreeSurface(this->_spriteSheet); }

SDL_Surface* SpriteManager::getSpriteSheet() const { return this->_spriteSheet; }

LevelSpriteManager::LevelSpriteManager(const std::string& spriteSheetPath) : SpriteManager(spriteSheetPath) {}
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

RobotSpriteManager::RobotSpriteManager(const std::string& spriteSheetPath) : SpriteManager(spriteSheetPath) {}

PlayerSpriteManager::PlayerSpriteManager(const std::string& spriteSheetPath) : SpriteManager(spriteSheetPath) {}

TextSpriteManager::TextSpriteManager(const std::string& spriteSheetPath) : SpriteManager(spriteSheetPath) {}
