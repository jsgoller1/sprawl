#pragma once

#include "SpriteManager.hh"

enum BulletColor {
  GREEN = 0,
  MUSTARD = 1,
  RED = 2,
  BLUEGREEN = 3,
  MAGENTA = 4,
  YELLOW = 5,
  PINK = 6,
  GRAY = 7,
  TEAL = 8,
  WHITE = 9
};

// Fwd decl
class Sprite;

class BulletSpriteManager : public SpriteManager {
 public:
  BulletSpriteManager(const std::string& spriteSheetPath);

  std::shared_ptr<Sprite> bulletVertical(const BulletColor bullet) const;
  std::shared_ptr<Sprite> bulletHorizontal(const BulletColor bullet) const;
  std::shared_ptr<Sprite> bulletNE(const BulletColor bullet) const;
  std::shared_ptr<Sprite> bulletSE(const BulletColor bullet) const;
};
