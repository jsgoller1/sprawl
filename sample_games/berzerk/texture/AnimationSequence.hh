#pragma once

#include <memory>
#include <vector>

#include "Sprite.hh"
#include "Time.hh"

class AnimationSequence {
  /*
   * AnimationSequence is an opaque container containing a selection of images from a spritesheet to be
   * used in an animation, along with logic/state for animating them.
   */
 public:
  AnimationSequence();
  AnimationSequence(const std::shared_ptr<Sprite> sprite);
  AnimationSequence(const std::vector<std::shared_ptr<Sprite>> sprites, const time_ms frameShowLength);
  void addSprite(const std::shared_ptr<Sprite> sprite);

  void setFrameShowLength(const time_ms frameShowLength);
  time_ms getFrameShowLength() const;

  std::shared_ptr<Sprite> getCurrentSprite() const;
  void update(const time_ms deltaT);
  void reset();

 private:
  time_ms _sinceLastUpdate = 0;
  time_ms _frameShowLength = 45;
  unsigned int _spriteIdx = 0;
  std::vector<std::shared_ptr<Sprite>> _sprites;
};
