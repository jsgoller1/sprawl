#include "SpriteManager.hh"

SpriteManager::SpriteManager(const std::string& spriteSheetPath) : _spriteSheetPath(spriteSheetPath) {}
LevelSpriteManager::LevelSpriteManager(const std::string& spriteSheetPath) : SpriteManager(spriteSheetPath) {}
RobotSpriteManager::RobotSpriteManager(const std::string& spriteSheetPath) : SpriteManager(spriteSheetPath) {}
PlayerSpriteManager::PlayerSpriteManager(const std::string& spriteSheetPath) : SpriteManager(spriteSheetPath) {}
TextSpriteManager::TextSpriteManager(const std::string& spriteSheetPath) : SpriteManager(spriteSheetPath) {}
