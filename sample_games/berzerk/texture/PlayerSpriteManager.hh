#pragma once

#include "SpriteManager.hh"

class PlayerSpriteManager : public SpriteManager {
 public:
  PlayerSpriteManager(const std::string& spriteSheetPath);

  std::shared_ptr<Sprite> movingE(const int frameNo) const;
  std::shared_ptr<Sprite> movingW(const int frameNo) const;
  std::shared_ptr<Sprite> dying(const int frameNo) const;

  std::shared_ptr<Sprite> shootingN() const;
  std::shared_ptr<Sprite> shootingE() const;
  std::shared_ptr<Sprite> shootingS() const;
  std::shared_ptr<Sprite> shootingW() const;
  std::shared_ptr<Sprite> shootingNE() const;
  std::shared_ptr<Sprite> shootingSE() const;
  std::shared_ptr<Sprite> shootingNW() const;
  std::shared_ptr<Sprite> shootingSW() const;
  std::shared_ptr<Sprite> standing() const;

  std::shared_ptr<Sprite> bulletVertical() const;
  std::shared_ptr<Sprite> bulletHorizontal() const;
  std::shared_ptr<Sprite> bulletNE() const;
  std::shared_ptr<Sprite> bulletSE() const;
};
