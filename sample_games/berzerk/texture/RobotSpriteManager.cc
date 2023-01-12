#include "RobotSpriteManager.hh"

RobotSpriteManager::RobotSpriteManager(const std::string& spriteSheetPath)
    : SpriteManager(spriteSheetPath, Vect2D::zero(), 0, 0, 0) {}
