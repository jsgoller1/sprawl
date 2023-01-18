#pragma once

#include "SpriteManager.hh"

class OttoSpriteManager : public SpriteManager {
 public:
  OttoSpriteManager(const std::string& spriteSheetPath);

  std::shared_ptr<Sprite> spawning(const int frameNo) const;
  std::shared_ptr<Sprite> full(const int frameNo) const;
  std::shared_ptr<Sprite> collapsed(const int frameNo) const;
};
