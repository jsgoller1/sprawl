#include "AnimationSequence.hh"

AnimationSequence::AnimationSequence(const std::string name, int loopLimit) : _name(name), _loopLimit(loopLimit) {
  this->_sprites = std::vector<std::shared_ptr<Sprite>>();
}

AnimationSequence::AnimationSequence(const std::string name, const std::shared_ptr<Sprite> sprite, int loopLimit)
    : _name(name), _loopLimit(loopLimit) {
  this->_sprites = std::vector<std::shared_ptr<Sprite>>{sprite};
}
AnimationSequence::AnimationSequence(const std::string name, const std::vector<std::shared_ptr<Sprite>> sprites,
                                     const time_ms frameShowLength, int loopLimit)
    : _name(name), _loopLimit(loopLimit), _frameShowLength(frameShowLength), _sprites(sprites) {}

void AnimationSequence::addSprite(const std::shared_ptr<Sprite> sprite) { this->_sprites.push_back(sprite); }

std::shared_ptr<Sprite> AnimationSequence::getCurrentSprite() const {
  if (not(this->_spriteIdx <= this->_sprites.size() - 1)) {
    return nullptr;
  }
  return this->_sprites[this->_spriteIdx];
}

bool AnimationSequence::loopsIndefinitely() { return this->_loopLimit == -1; }

bool AnimationSequence::isComplete() { return !this->loopsIndefinitely() && this->_loopCount >= this->_loopLimit; }

void AnimationSequence::update(const time_ms deltaT) {
  this->_sinceLastUpdate += deltaT;
  if (_sinceLastUpdate > _frameShowLength && !this->isComplete()) {
    this->_spriteIdx = (this->_spriteIdx + 1) % this->_sprites.size();
    this->_sinceLastUpdate = 0;

    if (this->_spriteIdx == 0) {
      this->_loopCount++;
    }
  }
}

void AnimationSequence::reset() { this->_spriteIdx = 0; }
