#pragma once
#include <SDL2/SDL.h>

#include <memory>
#include <string>

#include "Sprite.hh"
#include "Vect2D.hh"

class SpriteManager {
 public:
  SpriteManager(const std::string& spriteSheetPath);
  ~SpriteManager();
  SDL_Surface* getSpriteSheet() const;

 private:
  SDL_Surface* _spriteSheet;
};
class LevelSpriteManager : public SpriteManager {
 public:
  LevelSpriteManager(const std::string& spriteSheetPath);
  std::shared_ptr<Sprite> horizontalBorderWall() const;
  std::shared_ptr<Sprite> verticalBorderWall() const;
  std::shared_ptr<Sprite> horizontalInternalWall() const;
  std::shared_ptr<Sprite> verticalInternalWall() const;
  std::shared_ptr<Sprite> horizontalExitWall() const;
  std::shared_ptr<Sprite> verticalExitWall() const;
};

class RobotSpriteManager : public SpriteManager {
 public:
  RobotSpriteManager(const std::string& spriteSheetPath);
};

class PlayerSpriteManager : public SpriteManager {
 public:
  PlayerSpriteManager(const std::string& spriteSheetPath);

  std::shared_ptr<Sprite> standing() const;
  std::shared_ptr<Sprite> faceLeft() const;
  std::shared_ptr<Sprite> faceRight() const;
};
class TextSpriteManager : public SpriteManager {
 public:
  TextSpriteManager(const std::string& spriteSheetPath);
};
