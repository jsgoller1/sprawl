#include "OttoSpriteManager.hh"

#include "Configs.hh"

OttoSpriteManager::OttoSpriteManager(const std::string& spriteSheetPath)
    : SpriteManager(spriteSheetPath, TOP_LEFT, OTTO_SPRITE_WIDTH_PX, OTTO_SPRITE_HEIGHT_PX,
                    OTTO_SPRITE_BOUNDARY_WIDTH_PX) {}
