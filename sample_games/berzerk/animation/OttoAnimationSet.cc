#include "OttoAnimationSet.hh"

OttoAnimationSet::OttoAnimationSet(const OttoSpriteManager& ottoSpriteManager)
    : _ottoSpriteManager(ottoSpriteManager) {}

std::shared_ptr<AnimationSequence> OttoAnimationSet::spawning() const {
  (void)this->_ottoSpriteManager;
  return nullptr;
}
