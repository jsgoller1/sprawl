#include "AnimatedDrawingComponent.hh"

AnimatedDrawingComponent::AnimatedDrawingComponent(PositionComponent& positionComponent, const int height,
                                                   const int width, DrawingProxy& drawingProxy,
                                                   const std::shared_ptr<AnimationSequence> animation)
    : DrawingComponent(positionComponent, height, width, drawingProxy),
      _positionComponent(positionComponent),
      _animationSequence(animation) {}

std::shared_ptr<Sprite> AnimatedDrawingComponent::getCurrentSprite() const {
  return this->_animationSequence->getCurrentSprite();
}

void AnimatedDrawingComponent::updateAnimationSequence(const time_ms deltaT) {
  return this->_animationSequence->update(deltaT);
}

// AnimationSequence& AnimatedDrawingComponent::getAnimationSequence() const { return *this->_animationSequence; }

void AnimatedDrawingComponent::setAnimationSequence(const std::shared_ptr<AnimationSequence> animation) {
  this->_animationSequence = animation;
  // this->_animationSequence->reset();
}

void AnimatedDrawingComponent::draw() {
  this->getDrawingProxy().draw(this->_positionComponent.getPosition(), this->getWidth(), this->getHeight(),
                               this->_animationSequence->getCurrentSprite());
}
