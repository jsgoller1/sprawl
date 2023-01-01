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
  return std::make_shared<Sprite>(this->getSpriteSheet(), 19, 8, 54, 4);
}

RobotSpriteManager::RobotSpriteManager(const std::string& spriteSheetPath) : SpriteManager(spriteSheetPath) {}

PlayerSpriteManager::PlayerSpriteManager(const std::string& spriteSheetPath) : SpriteManager(spriteSheetPath) {}

TextSpriteManager::TextSpriteManager(const std::string& spriteSheetPath) : SpriteManager(spriteSheetPath) {}
