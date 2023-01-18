#include "RobotSpriteManager.hh"

constexpr int ROBOT_SPRITE_WIDTH_PX = 8;
constexpr int ROBOT_SPRITE_HEIGHT_PX = 11;
constexpr int ROBOT_SPRITE_BOUNDARY_WIDTH_PX = 1;
const Vect2D TOP_LEFT = Vect2D::zero();

RobotSpriteManager::RobotSpriteManager(const std::string& spriteSheetPath)
    : SpriteManager(spriteSheetPath, TOP_LEFT, ROBOT_SPRITE_WIDTH_PX, ROBOT_SPRITE_HEIGHT_PX,
                    ROBOT_SPRITE_BOUNDARY_WIDTH_PX) {}

std::shared_ptr<Sprite> RobotSpriteManager::idle(const int frameNo) const { return this->getSprite(frameNo, 0); }
