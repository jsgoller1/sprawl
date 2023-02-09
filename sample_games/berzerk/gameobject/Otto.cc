#include "Otto.hh"

#include "Configs.hh"

Otto::Otto(const Vect2D& position, DrawingProxy& drawingProxy, PlayerPositionProxy& playerPositionProxy,
           const OttoSpriteManager& ottoSpriteManager)
    : GameObject(position, Vect2D::zero()),
      _playerPositionProxy(playerPositionProxy),
      _ottoSpriteManager(ottoSpriteManager) {
  this->_ottoAnimationSet = std::unique_ptr<OttoAnimationSet>(new OttoAnimationSet(this->_ottoSpriteManager));
  this->_drawingComponent = std::unique_ptr<AnimatedDrawingComponent>(
      new AnimatedDrawingComponent(this->getPositionComponent(), OTTO_SPRITE_HEIGHT_PX, OTTO_SPRITE_WIDTH_PX,
                                   drawingProxy, this->_ottoAnimationSet->spawning()));
}

void Otto::update(const TimerProxy& timerProxy) {
  (void)timerProxy;
  (void)this->_state;
  (void)this->_playerPositionProxy;
}

AnimatedDrawingComponent& Otto::getDrawingComponent() const { return *this->_drawingComponent; }

void Otto::resolveCollision(GameObject& target) {
  // Otto is invulnerable, nothing to do here.
  (void)target;
}
