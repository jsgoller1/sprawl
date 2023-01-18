#include "OttoSpriteManager.hh"

constexpr int OTTO_SPRITE_WIDTH_PX = 8;
constexpr int OTTO_SPRITE_HEIGHT_PX = 16;
constexpr int OTTO_SPRITE_BOUNDARY_WIDTH_PX = 1;
const Vect2D TOP_LEFT = Vect2D::zero();

OttoSpriteManager::OttoSpriteManager(const std::string& spriteSheetPath)
    : SpriteManager(spriteSheetPath, TOP_LEFT, OTTO_SPRITE_WIDTH_PX, OTTO_SPRITE_HEIGHT_PX,
                    OTTO_SPRITE_BOUNDARY_WIDTH_PX) {}
