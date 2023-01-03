#pragma once

#include <memory>
#include <vector>

#include "Sprite.hh"

class AnimationSequence {
  /*
   * AnimationSequence is an opaque container containing a selection of images from a spritesheet to be
   * used in an animation, along with logic/state for animating them.
   */
 public:
  AnimationSequence();
  AnimationSequence(const std::shared_ptr<Sprite> sprite);
  AnimationSequence(const std::vector<std::shared_ptr<Sprite>>& spriteCollection);

  std::shared_ptr<Sprite> getCurrentSprite() const;
  std::shared_ptr<Sprite> getNextSprite();
  void resetSequence();

 private:
  unsigned int _spriteIdx = 0;
  std::vector<std::shared_ptr<Sprite>> _sprites;
};
