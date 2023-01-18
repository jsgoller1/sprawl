#include "AnimationSequence.hh"

AnimationSequence::AnimationSequence(const std::string name) : _name(name) {
  this->_sprites = std::vector<std::shared_ptr<Sprite>>();
}

AnimationSequence::AnimationSequence(const std::string name, const std::shared_ptr<Sprite> sprite) : _name(name) {
  this->_sprites = std::vector<std::shared_ptr<Sprite>>{sprite};
}
AnimationSequence::AnimationSequence(const std::string name, const std::vector<std::shared_ptr<Sprite>> sprites,
                                     const time_ms frameShowLength)
    : _name(name), _frameShowLength(frameShowLength), _sprites(sprites) {}

void AnimationSequence::addSprite(const std::shared_ptr<Sprite> sprite) { this->_sprites.push_back(sprite); }

std::shared_ptr<Sprite> AnimationSequence::getCurrentSprite() const {
  if (not(this->_spriteIdx <= this->_sprites.size() - 1)) {
    return nullptr;
  }
  return this->_sprites[this->_spriteIdx];
}

void AnimationSequence::update(const time_ms deltaT) {
  this->_sinceLastUpdate += deltaT;
  if (_sinceLastUpdate > _frameShowLength) {
    this->_spriteIdx = (this->_spriteIdx + 1) % this->_sprites.size();
    this->_sinceLastUpdate = 0;
  }
}

void AnimationSequence::reset() { this->_spriteIdx = 0; }
