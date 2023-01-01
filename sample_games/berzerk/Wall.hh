#pragma once

#include "GameObject.hh"
#include "SpriteManager.hh"

constexpr int WALL_THICCNESS = 10;
constexpr int WALL_LENGTH = 100;
constexpr int VERTICAL_WALL_WIDTH = WALL_THICCNESS;
constexpr int VERTICAL_WALL_HEIGHT = WALL_LENGTH;
constexpr int HORIZONTAL_WALL_WIDTH = WALL_LENGTH;
constexpr int HORIZONTAL_WALL_HEIGHT = WALL_THICCNESS;

class Wall : public GameObject {
 public:
  Wall(const Vect2D& position, const int height, const int width, const LevelSpriteManager& levelSpriteManager,
       DrawingProxy& drawingProxy);

  const LevelSpriteManager& getSpriteManager() const override;
  std::shared_ptr<Sprite> getCurrentSprite() const override;
  void resolveCollision(GameObject& target) override;

 private:
  const LevelSpriteManager& _levelSpriteManager;
};
