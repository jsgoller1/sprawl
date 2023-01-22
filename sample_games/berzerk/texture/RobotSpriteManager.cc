#include "RobotSpriteManager.hh"

#include "Configs.hh"

RobotSpriteManager::RobotSpriteManager(const std::string& spriteSheetPath)
    : SpriteManager(spriteSheetPath, TOP_LEFT, ROBOT_SPRITE_WIDTH_PX, ROBOT_SPRITE_HEIGHT_PX,
                    ROBOT_SPRITE_BOUNDARY_WIDTH_PX) {}

std::shared_ptr<Sprite> RobotSpriteManager::idle(const int frameNo) const { return this->getSprite(frameNo, 0); }

std::shared_ptr<Sprite> RobotSpriteManager::movingN(const int frameNo) const { return this->getSprite(3 + frameNo, 2); }
std::shared_ptr<Sprite> RobotSpriteManager::movingS(const int frameNo) const { return this->getSprite(frameNo, 2); }
std::shared_ptr<Sprite> RobotSpriteManager::movingE(const int frameNo) const { return this->getSprite(frameNo, 1); }
std::shared_ptr<Sprite> RobotSpriteManager::movingW(const int frameNo) const { return this->getSprite(2 + frameNo, 1); }
std::shared_ptr<Sprite> RobotSpriteManager::dying(const int frameNo) const {
  (void)frameNo;
  return nullptr;
}
std::shared_ptr<Sprite> RobotSpriteManager::dead() const { return this->getSprite(4, 1); }

std::shared_ptr<Sprite> RobotSpriteManager::shootingN() const { return this->getSprite(0, 0); }
std::shared_ptr<Sprite> RobotSpriteManager::shootingE() const { return this->getSprite(0, 1); }
std::shared_ptr<Sprite> RobotSpriteManager::shootingS() const { return this->getSprite(3, 0); }
std::shared_ptr<Sprite> RobotSpriteManager::shootingW() const { return this->getSprite(3, 1); }
std::shared_ptr<Sprite> RobotSpriteManager::shootingNE() const { return this->shootingE(); }
std::shared_ptr<Sprite> RobotSpriteManager::shootingSE() const { return this->shootingE(); }
std::shared_ptr<Sprite> RobotSpriteManager::shootingNW() const { return this->shootingW(); }
std::shared_ptr<Sprite> RobotSpriteManager::shootingSW() const { return this->shootingW(); }
