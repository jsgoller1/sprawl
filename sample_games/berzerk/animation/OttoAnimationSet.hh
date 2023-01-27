#pragma once
#include <memory>

#include "AnimationSequence.hh"

// Fwd decl
class OttoSpriteManager;

class OttoAnimationSet {
 public:
  OttoAnimationSet(const OttoSpriteManager& ottoSpriteManager);
  std::shared_ptr<AnimationSequence> spawning() const;

 private:
  const OttoSpriteManager& _ottoSpriteManager;
};
