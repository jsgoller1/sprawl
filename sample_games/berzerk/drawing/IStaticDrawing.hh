#pragma once

#include <memory>

#include "IDrawing.hh"

class IStaticDrawing : public IDrawing {
 public:
  IStaticDrawing(PositionComponent& _positionComponent, const int height, const int width, DrawingProxy& drawingProxy,
                 const std::shared_ptr<Sprite> sprite);

  // Get the current sprite, which is the only sprite we ever use
  std::shared_ptr<Sprite> getCurrentSprite() const override;

 private:
  std::shared_ptr<Sprite> _sprite;
};
