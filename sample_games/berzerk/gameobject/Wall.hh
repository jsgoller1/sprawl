#pragma once

#include <memory>

#include "Configs.hh"
#include "GameObject.hh"
#include "LevelSpriteManager.hh"
#include "Screen.hh"
#include "StaticDrawingComponent.hh"

Vect2D getWallPosition(unsigned wallIndex);

class Wall : public GameObject {
 public:
  Wall(const Wall& copy);
  static Wall HorizontalBorderWall(const Vect2D& center, const LevelSpriteManager& levelSpriteManager,
                                   DrawingProxy& drawingProxy) {
    return Wall(center, HORIZONTAL_WALL_HEIGHT, HORIZONTAL_WALL_WIDTH, levelSpriteManager.horizontalBorderWall(),
                drawingProxy);
  }

  static Wall VerticalBorderWall(const Vect2D& center, const LevelSpriteManager& levelSpriteManager,
                                 DrawingProxy& drawingProxy) {
    return Wall(center, VERTICAL_WALL_HEIGHT, VERTICAL_WALL_WIDTH, levelSpriteManager.verticalBorderWall(),
                drawingProxy);
  }

  static Wall HorizontalInternalWall(const Vect2D& center, const LevelSpriteManager& levelSpriteManager,
                                     DrawingProxy& drawingProxy) {
    return Wall(center, HORIZONTAL_WALL_HEIGHT, HORIZONTAL_WALL_WIDTH, levelSpriteManager.horizontalInternalWall(),
                drawingProxy);
  }

  static Wall VerticalInternalWall(const Vect2D& center, const LevelSpriteManager& levelSpriteManager,
                                   DrawingProxy& drawingProxy) {
    return Wall(center, VERTICAL_WALL_HEIGHT, VERTICAL_WALL_WIDTH, levelSpriteManager.verticalInternalWall(),
                drawingProxy);
  }

  static Wall HorizontalExitWall(const Vect2D& center, const LevelSpriteManager& levelSpriteManager,
                                 DrawingProxy& drawingProxy) {
    return Wall(center, HORIZONTAL_WALL_HEIGHT, HORIZONTAL_WALL_WIDTH, levelSpriteManager.horizontalExitWall(),
                drawingProxy);
  }

  static Wall VerticalExitWall(const Vect2D& center, const LevelSpriteManager& levelSpriteManager,
                               DrawingProxy& drawingProxy) {
    return Wall(center, VERTICAL_WALL_HEIGHT, VERTICAL_WALL_WIDTH, levelSpriteManager.verticalExitWall(), drawingProxy);
  }

  void resolveCollision(GameObject& target) override;
  StaticDrawingComponent& getDrawingComponent() const override;

 protected:
  Wall(const Vect2D& position, const int height, const int width, const std::shared_ptr<Sprite> sprite,
       DrawingProxy& drawingProxy);

 private:
  std::unique_ptr<StaticDrawingComponent> _drawingComponent;
};
