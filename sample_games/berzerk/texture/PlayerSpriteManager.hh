#pragma once

#include "SpriteManager.hh"

class PlayerSpriteManager : public SpriteManager {
 public:
  PlayerSpriteManager(const std::string& spriteSheetPath);

  std::shared_ptr<Sprite> standing() const;
};
