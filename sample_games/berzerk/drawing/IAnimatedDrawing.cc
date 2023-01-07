#include "IAnimatedDrawing.hh"

IAnimatedDrawing::IAnimatedDrawing(PositionComponent& positionComponent, const int height, const int width,
                                   DrawingProxy& drawingProxy, const std::shared_ptr<AnimationSequence> animation)
    : IDrawing(positionComponent, height, width, drawingProxy),
      _positionComponent(positionComponent),
      _animationSequence(animation) {}

std::shared_ptr<Sprite> IAnimatedDrawing::getCurrentSprite() const {
  return this->_animationSequence->getCurrentSprite();
}

void IAnimatedDrawing::updateAnimationSequence() { return this->_animationSequence->nextSprite(); }

// AnimationSequence& IAnimatedDrawing::getAnimationSequence() const { return *this->_animationSequence; }

void IAnimatedDrawing::setAnimationSequence(const std::shared_ptr<AnimationSequence> animation) {
  this->_animationSequence = animation;
  this->_animationSequence->reset();
}

void IAnimatedDrawing::draw() {
  this->getDrawingProxy().draw(this->_positionComponent.getPosition(), this->getWidth(), this->getHeight(),
                               this->_animationSequence->getCurrentSprite());
}
