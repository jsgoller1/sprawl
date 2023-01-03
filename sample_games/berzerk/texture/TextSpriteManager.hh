#pragma once

#include "SpriteManager.hh"

class TextSpriteManager : public SpriteManager {
 public:
  TextSpriteManager(const std::string& spriteSheetPath);
};
