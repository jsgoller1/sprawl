#pragma once

#include <map>

#include "AnimatedDrawingComponent.hh"
#include "Configs.hh"
#include "GameObject.hh"
#include "IShooting.hh"
#include "PlayerAnimationSet.hh"
#include "PlayerAudioComponent.hh"
#include "State.hh"

// Forward decls
class AnimationSequence;
class InputHandler;
class PlayerSpriteManager;

class Player : public GameObject, public IShooting {
 public:
  Player(const Vect2D& position, const Vect2D& velocity, LevelShootingProxy& shootingProxy, DrawingProxy& drawingProxy,
         const PlayerSpriteManager& playerSpriteManager);

  AnimatedDrawingComponent& getDrawingComponent() const override;

  void resolveCollision(GameObject& target) override;
  void update(const InputHandler& inputHandler, const TimerProxy& timerProxy);
  void draw();
  bool isDead() const;

 private:
  CharacterState _state;
  time_ms _sinceLastShot;
  PlayerAudioComponent _playerAudioComponent = PlayerAudioComponent();
  std::unique_ptr<PlayerAnimationSet> _playerAnimationSet = nullptr;
  std::unique_ptr<AnimatedDrawingComponent> _drawingComponent = nullptr;

  CharacterState getNewState(const CharacterState currentState, const InputHandler& inputHandler) const;
  Vect2D getNewVelocity(const CharacterState currentState, const InputHandler& inputHandler) const;
  void updateAnimation(const TimerProxy& timerProxy, const Direction& movementDirection, const CharacterState state);
  void shootingBehavior(const TimerProxy& timerProxy, const Direction& shootingDirection);
};
