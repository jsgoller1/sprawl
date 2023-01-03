#include "AnimationSequence.hh"

AnimationSequence::AnimationSequence() { this->_sprites = std::vector<std::shared_ptr<Sprite>>(); }

AnimationSequence::AnimationSequence(const std::shared_ptr<Sprite> sprite) {
  this->_sprites = std::vector<std::shared_ptr<Sprite>>{sprite};
}
AnimationSequence::AnimationSequence(const std::vector<std::shared_ptr<Sprite>>& spriteCollection) {
  this->_sprites = std::vector<std::shared_ptr<Sprite>>(spriteCollection);
}

std::shared_ptr<Sprite> AnimationSequence::getCurrentSprite() const {
  if (not(this->_spriteIdx <= this->_sprites.size() - 1)) {
    return nullptr;
  }
  return this->_sprites[this->_spriteIdx];
}

std::shared_ptr<Sprite> AnimationSequence::getNextSprite() {
  this->_spriteIdx = (this->_spriteIdx + 1) % this->_sprites.size();
  return this->getCurrentSprite();
}
void AnimationSequence::resetSequence() { this->_spriteIdx = 0; }
