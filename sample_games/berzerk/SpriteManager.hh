#pragma once
#include <SDL2/SDL.h>

#include <memory>
#include <string>

#include "Vect2D.hh"

class SpriteManager {
 public:
  SpriteManager(const std::string& spriteSheetPath);
  std::shared_ptr<SDL_Surface> loadSpriteData(const Vect2D& topLeft, const int width, const int height);

 private:
  std::string _spriteSheetPath;
};
class LevelSpriteManager : public SpriteManager {
 public:
  LevelSpriteManager(const std::string& spriteSheetPath);
  std::shared_ptr<SDL_Surface> horizontalBorderWall();
  std::shared_ptr<SDL_Surface> verticalBorderWall();
  std::shared_ptr<SDL_Surface> horizontalInternalWall();
  std::shared_ptr<SDL_Surface> verticalInternalWall();
};

class RobotSpriteManager : public SpriteManager {
 public:
  RobotSpriteManager(const std::string& spriteSheetPath);
};

class PlayerSpriteManager : public SpriteManager {
 public:
  PlayerSpriteManager(const std::string& spriteSheetPath);

  std::shared_ptr<SDL_Surface> standing();
  std::shared_ptr<SDL_Surface> faceLeft();
  std::shared_ptr<SDL_Surface> faceRight();
};
class TextSpriteManager : public SpriteManager {
 public:
  TextSpriteManager(const std::string& spriteSheetPath);
};
