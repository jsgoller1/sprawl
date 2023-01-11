#pragma once

#include <memory>

#include "AnimationSequence.hh"
#include "IDrawing.hh"
#include "Time.hh"

// Forward decls
class PositionComponent;

class IAnimatedDrawing : public IDrawing {
 public:
  IAnimatedDrawing(PositionComponent& _positionComponent, const int height, const int width, DrawingProxy& drawingProxy,
                   const std::shared_ptr<AnimationSequence> animationSequence);

  // Get the current sprite by getting the next animation
  void draw() override;
  std::shared_ptr<Sprite> getCurrentSprite() const override;

  void updateAnimationSequence(const time_ms deltaT);
  void setAnimationSequence(const std::shared_ptr<AnimationSequence> animation);
  // AnimationSequence& getAnimationSequence() const;

 private:
  PositionComponent& _positionComponent;
  std::shared_ptr<AnimationSequence> _animationSequence;
};
